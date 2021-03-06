#include <include/Scale.h>
#include "BoundaryObject.h"

BoundaryObject::BoundaryObject(string s, float data) : Object(data) {
    readObj(s);

    // TO DO: Cal fer un recorregut de totes les cares per a posar-les com Triangles
    // Cal recorrer l'estructura de l'objecte segons cara-vertexs que es carrega

    //Per a guardar els vertex externs de la figura en questio
    float minX, maxX = vertexs[cares[0].idxVertices[0]].x;
    float minY, maxY = vertexs[cares[0].idxVertices[0]].y;
    float minZ, maxZ = vertexs[cares[0].idxVertices[0]].z;


    //recoregut de les cares i creacio de triangles
    for (unsigned int i = 0; i < cares.size(); i++) {
        Cara temp = cares[i];

        vec4 v1 = vertexs[temp.idxVertices[0]];
        vec4 v2 = vertexs[temp.idxVertices[1]];
        vec4 v3 = vertexs[temp.idxVertices[2]];

        Triangle *tri = new Triangle(vec3(v1.x, v1.y, v1.z), vec3(v2.x, v2.y, v2.z), vec3(v3.x, v3.y, v3.z), data);
        this->triangles.push_back(tri);
    }

    for (unsigned int i = 0; i < vertexs.size(); i++) {
        maxX = std::max(vertexs[i].x, maxX);
        minX = std::min(vertexs[i].x, minX);
        maxZ = std::max(vertexs[i].z, maxZ);
        minZ = std::min(vertexs[i].z, minZ);
        maxY = std::max(vertexs[i].y, maxY);
        minY = std::min(vertexs[i].y, minY);
    }
    vertexs.clear();
    cares.clear();
}

BoundaryObject::~BoundaryObject() {
    for (unsigned int i = 0; i < triangles.size(); i++) {
        if (triangles[i]) {
            if (dynamic_cast<Triangle *>(triangles[i])) {
                delete (Triangle *) (triangles[i]);
            }
        }
    }
}

void BoundaryObject::aplicaTG(TG *t) {
    if (dynamic_cast<Translate *>(t)) for (unsigned int i = 0; i < triangles.size(); i++) triangles[i]->aplicaTG(t);
    if (dynamic_cast<Scale *>(t)) for (unsigned int i = 0; i < triangles.size(); i++) triangles[i]->aplicaTG(t);
}

bool BoundaryObject::intersection(const Ray &r, float t_min, float t_max, IntersectionInfo &info) const {
    float t_menor(std::numeric_limits<float>::infinity());
    bool intersection = false;

    for (Triangle* t : triangles)
        if(t->intersection(r,t_min,t_max,info)){
            if(info.t < t_menor)
                t_menor = info.t;
            intersection = true;
        }

    // aqui cal actualitzar IntersectionInfo
    info.t = t_menor;
    info.p = r.pointAtParameter(info.t);
    info.normal = vec3(info.p.x,0,info.p.z);
    info.mat_ptr = material;

    return intersection;
}


// Llegeix un fitxer .obj
// Si el fitxer referencia fitxers de materials (.mtl), encara no es llegeixen
// Tots els elements del fitxer es llegeixen com a un unic objecte.
void BoundaryObject::readObj(string filename) {
    FILE *fp = fopen(filename.c_str(), "rb");
    if (!fp) {
        cout << "No puc obrir el fitxer " << endl;
    } else {
        while (true) {
            char *comment_ptr = ReadFile::fetch_line(fp);

            if (comment_ptr == (char *) -1)  /* end-of-file */
                break;

            /* did we get a comment? */
            if (comment_ptr) {
                //make_comment (comment_ptr);
                continue;
            }

            /* if we get here, the line was not a comment */
            int nwords = ReadFile::fetch_words();

            /* skip empty lines */
            if (nwords == 0)
                continue;

            char *first_word = ReadFile::words[0];

            if (!strcmp(first_word, "v")) {
                if (nwords < 4) {
                    fprintf(stderr, "Too few coordinates: '%s'", ReadFile::str_orig);
                    exit(-1);
                }

                string sx(ReadFile::words[1]);
                string sy(ReadFile::words[2]);
                string sz(ReadFile::words[3]);
                double x = atof(sx.c_str());
                double y = atof(sy.c_str());
                double z = atof(sz.c_str());

                if (nwords == 5) {
                    string sw(ReadFile::words[4]);
                    double w = atof(sw.c_str());
                    x /= w;
                    y /= w;
                    z /= w;
                }
                // S'afegeix el vertex a l'objecte
                vertexs.push_back(vec4(x, y, z, 1));

            } else if (!strcmp(first_word, "vn")) {
            } else if (!strcmp(first_word, "vt")) {
            } else if (!strcmp(first_word, "f")) {
                // S'afegeix la cara a l'objecte
                // A modificar si es vol carregar mes de un objecte
                construeix_cara(&ReadFile::words[1], nwords - 1, this, 0);
            }
                // added
            else if (!strcmp(first_word, "mtllib")) {
                //read_mtllib (&words[1], nwords-1, matlib, filename);
            } else if (!strcmp(first_word, "usemtl")) {
                //int size = strlen(words[1])-1;
                //while (size && (words[1][size]=='\n' || words[1][size]=='\r') ) words[1][size--]=0;
                //currentMaterial = matlib.index(words[1]);
            }
                // fadded
            else {
                //fprintf (stderr, "Do not recognize: '%s'\n", str_orig);
            }
        }
    }
    fclose(fp);
}

/**
 * @brief BoundaryObject::construeix_cara
 * @param words
 * @param nwords
 * @param objActual
 * @param vindexUlt
 */
void BoundaryObject::construeix_cara(char **words, int nwords, BoundaryObject *objActual, int vindexUlt) {
    Cara face;

    for (int i = 0; i < nwords; i++) {
        int vindex;
        int nindex;
        int tindex;

        if ((words[i][0] >= '0') && (words[i][0] <= '9')) {
            ReadFile::get_indices(words[i], &vindex, &tindex, &nindex);

#if 0
            printf ("vtn: %d %d %d\n", vindex, tindex, nindex);
#endif

            /* store the vertex index */

            if (vindex > 0)       /* indices are from one, not zero */
                face.idxVertices.push_back(vindex - 1 - vindexUlt);
            else if (vindex < 0)  /* negative indices mean count backwards */
                face.idxVertices.push_back(objActual->vertexs.size() + vindex);
            else {
                fprintf(stderr, "Zero indices not allowed: '%s'\n", ReadFile::str_orig);
                exit(-1);
            }
        }
    }
    face.color = vec4(1.0, 0.0, 0.0, 1.0);
    objActual->cares.push_back(face);
}