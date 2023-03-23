#include "HypoGl/Primitives.h"
#include "HypoGl/DataStructures.h"

#include <GL/glut.h>
#include <unordered_map>
#include <vector>
#include <string>
#include <cmath>

using Point = Vector3f;
using UV = Vector2f;
using Face = std::vector<std::pair<size_t, UV>>;

namespace Primitives
{
    void Cube()
    {
        auto points = std::unordered_map<std::string, Point>();
            points["A"] = {-.5f, -.5f, .5f};
            points["B"] = {.5f, -.5f, .5f};
            points["C"] = {.5f, -.5f, -.5f};
            points["D"] = {-.5f, -.5f, -.5f};
            points["E"] = {-.5f, .5f, .5f};
            points["F"] = {.5f, .5f, .5f};
            points["G"] = {.5f, .5f, -.5f};
            points["H"] = {-.5f, .5f, -.5f};

        // Face EFBA
        glBegin(GL_QUADS);
            glTexCoord2f(.375f, .25f);  glVertex3f(points["E"].x, points["E"].y, points["E"].z);
            glTexCoord2f(.625f, .25f);  glVertex3f(points["F"].x, points["F"].y, points["F"].z);
            glTexCoord2f(.625f, .5f);   glVertex3f(points["B"].x, points["B"].y, points["B"].z);
            glTexCoord2f(.375f, .5f);   glVertex3f(points["A"].x, points["A"].y, points["A"].z);
        glEnd();

        // Face EFGH
        glBegin(GL_QUADS);
            glTexCoord2f(.375f, .25f);  glVertex3f(points["E"].x, points["E"].y, points["E"].z);
            glTexCoord2f(.625f, .25f);  glVertex3f(points["F"].x, points["F"].y, points["F"].z);
            glTexCoord2f(.625f, 0.f);   glVertex3f(points["G"].x, points["G"].y, points["G"].z);
            glTexCoord2f(.375f, 0.f);   glVertex3f(points["H"].x, points["H"].y, points["H"].z);
        glEnd();

        // Face GCDH
        glBegin(GL_QUADS);
            glTexCoord2f(.625f, 1.f);   glVertex3f(points["G"].x, points["G"].y, points["G"].z);
            glTexCoord2f(.625f, .75);   glVertex3f(points["C"].x, points["C"].y, points["C"].z);
            glTexCoord2f(.375f, .75f);  glVertex3f(points["D"].x, points["D"].y, points["D"].z);
            glTexCoord2f(.375f, 1.f);   glVertex3f(points["H"].x, points["H"].y, points["H"].z);
        glEnd();

        // Face BADC
        glBegin(GL_QUADS);
            glTexCoord2f(.625f, .5f);   glVertex3f(points["B"].x, points["B"].y, points["B"].z);
            glTexCoord2f(.375f, .5f);   glVertex3f(points["A"].x, points["A"].y, points["A"].z);
            glTexCoord2f(.375f, .75f);  glVertex3f(points["D"].x, points["D"].y, points["D"].z);
            glTexCoord2f(.625f, .75f);  glVertex3f(points["C"].x, points["C"].y, points["C"].z);
        glEnd();

        // Face FBCG
        glBegin(GL_QUADS);
            glTexCoord2f(.625f, .25f);  glVertex3f(points["F"].x, points["F"].y, points["F"].z);
            glTexCoord2f(.625f, .5f);   glVertex3f(points["B"].x, points["B"].y, points["B"].z);
            glTexCoord2f(.875f, .5f);   glVertex3f(points["C"].x, points["C"].y, points["C"].z);
            glTexCoord2f(.875f, .25f);  glVertex3f(points["G"].x, points["G"].y, points["G"].z);
        glEnd();

        // Face EHDA
        glBegin(GL_QUADS);
            glTexCoord2f(.375f, .25f);  glVertex3f(points["E"].x, points["E"].y, points["E"].z);
            glTexCoord2f(.125f, .25f);  glVertex3f(points["H"].x, points["H"].y, points["H"].z);
            glTexCoord2f(.125f, .5f);   glVertex3f(points["D"].x, points["D"].y, points["D"].z);
            glTexCoord2f(.375f, .5f);   glVertex3f(points["A"].x, points["A"].y, points["A"].z);
        glEnd();
    }

    void Sphere()
    {
        size_t NM = 50, NP = 50;
        float r = .5f;

        std::vector<Point> points;

        for(size_t i = 0 ; i < NM ; i++)
        {
            for(size_t j = 1 ; j < NP + 1 ; j++)
            {
                float theta = i * 2 * M_PI / NM;
                float phi = j * M_PI / (NP + 1) - M_PI / 2.f;

                Point p;
                    p.x = r * std::cos(theta) * std::cos(phi);
                    p.y = r * std::sin(theta) * std::cos(phi);
                    p.z = r * sin(phi);

                points.push_back(p);
            }
        }

        points.push_back({0.f, 0.f, -r}); // South
        points.push_back({0.f, 0.f, r}); // North

        std::vector<Face> faces;

        for(size_t i = 0 ; i < NM ; i++)
        {
            Face top, bottom;

            bottom.push_back({points.size() - 2      , UV(i / (float)NM      , 1.f)});
            bottom.push_back({points.size() - 2      , UV((i + 1) / (float)NM, 1.f)});
            bottom.push_back({i * NP                 , UV((i + 1) / (float)NM, 1.f - 1.f / (float)(NP + 2))});
            bottom.push_back({(i + 1) % NM * NP      , UV(i / (float)NM      , 1.f - 1.f / (float)(NP + 2))});

            faces.push_back(bottom);

            top.push_back({i * NP + NM - 1           , UV(i / (float)NM      , 1.f / (float)(NP + 2))});
            top.push_back({(i + 1) % NM * NP + NM - 1, UV((i + 1) / (float)NM, 1.f / (float)(NP + 2))});
            top.push_back({points.size() - 1         , UV((i + 1) / (float)NM, 0.f)});
            top.push_back({points.size() - 1         , UV(i / (float)NM      , 0.f)});

            faces.push_back(top);

            for(size_t j = 0 ; j < NP - 1 ; j++)
            {
                Face f;
                    f.push_back({i * NP + j                 , UV(i / (float)NM           , 1.f - (j + 1) / (float)(NP + 2))});
                    f.push_back({((i + 1) % NM) * NP + j    , UV((i + 1) / (float)NM     , 1.f - (j + 1) / (float)(NP + 2))});
                    f.push_back({((i + 1) % NM) * NP + j + 1, UV((i + 1) / (float)NM     , 1.f - (j + 2) / (float)(NP + 2))});
                    f.push_back({i * NP + j + 1             , UV(i / (float)NM           , 1.f - (j + 2) / (float)(NP + 2))});

                faces.push_back(f);
            }
        }

        glPushMatrix();
        glRotatef(-90.f, 1.0, 0.0, 0.f);

        for(const auto& face : faces)
        {
            glBegin(GL_QUADS);
                glTexCoord2f(face[0].second.x, face[0].second.y); glVertex3f(points[face[0].first].x, points[face[0].first].y, points[face[0].first].z);
                glTexCoord2f(face[1].second.x, face[1].second.y); glVertex3f(points[face[1].first].x, points[face[1].first].y, points[face[1].first].z);
                glTexCoord2f(face[2].second.x, face[2].second.y); glVertex3f(points[face[2].first].x, points[face[2].first].y, points[face[2].first].z);
                glTexCoord2f(face[3].second.x, face[3].second.y); glVertex3f(points[face[3].first].x, points[face[3].first].y, points[face[3].first].z);
            glEnd();
        }

        glPopMatrix();
    }

    void Line()
    {
        glPushMatrix();

        glTranslatef(0.f, .5f, 0.f);
        glScalef(.1f, 1.f, .1f);
        glutSolidCube(1.0);

        glPopMatrix();
    }

    void Arrow()
    {
        Line();

        glPushMatrix();

        glTranslatef(0.f, 1.f, 0.f);
        glRotatef(-90.f, 1.f, 0.f, 0.f);
        glutSolidCone(.25, .5, 20, 20);

        glPopMatrix();
    }
}
