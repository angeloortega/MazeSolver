#ifndef GRAPH_INCLUDED
#define GRAPH_INCLUDED
#define INFINITE 999999
#define UNDEFINED -1
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include "LinkedStack.h"
#include "LinkedList.h"
using namespace std;

class Vertex
{
	public:
		int x;
		int y;
		Vertex(int xPos, int yPos)
		{
			x = xPos;
			y = yPos;
		}
};

class Graph
{
	private:
		static const int NULL_EDGE = 0;
		vector<Vertex*> vertices;
		vector<bool> marks;			// marks[i] is mark for vertices[i]
		int nmbVertices;
		int maxVertices;
		vector< vector<int> > edges;

	public:
		// constructor
		Graph(int size=600)
		{
			nmbVertices = 0;
			maxVertices = size;

			vertices.resize(size);
			for (int i=0;i<size;i++)	// init vertices
				vertices[i] = NULL;

			marks.resize(size);

			int rows = size;
			int columns = size;
			edges.resize(rows, vector<int>(columns, 0));
		}
        LinkedList<Vertex*> getVertices(){
            LinkedList<Vertex*> newVertices;
            for(int i = 0; i < (int)vertices.size(); i++){
                newVertices.append(vertices[i]);
            }
            return newVertices;
        }
		bool is_empty()
		{
			if (nmbVertices == 0)
				return true;
			else
				return false;
		}

		bool is_full()
		{
			if (nmbVertices == maxVertices)
				return true;
			else
				return false;
		}

		void add_vertex(Vertex* aVertex)
		{
			vertices[nmbVertices] = aVertex;
			for (int i=0; i<maxVertices; i++)
			{
				edges[nmbVertices][i] = NULL_EDGE;
				edges[i][nmbVertices] = NULL_EDGE;
			}
			nmbVertices++;
		}

		void add_edge(int fromVertex, int toVertex, int weight)
		{
			int row;
			int column;

			row = index_is(vertices[fromVertex]);
			column = index_is(vertices[toVertex]);
			edges[row][column] = weight;
		}

		int weight_is(int fromVertex, int toVertex)
			// If edge from fromVertex to toVertex exists, returns the weight of edge;
			// otherwise, returns a special “null-edge” value.
		{
			int row;
			int column;

			row = index_is(vertices[fromVertex]);
			column = index_is(vertices[toVertex]);
			return edges[row][column];
		}

		int index_is(Vertex* aVertex)
		{
			int i = 0;
			while (i < nmbVertices)
			{
				if (vertices[i] == aVertex)
					return i;
				i++;
			}
			return -1;
		}
        LinkedStack<int> get_neighbors(int vertex){
            LinkedStack<int> neighbors;
            for (int i=0; i<nmbVertices; i++)
				{
					if (edges[vertex][i] != NULL_EDGE)	// if adj vertex
					{
                        neighbors.push(i);
					}
				}
            return neighbors;
        }
		Vertex* get_vertex(int pos)
		{
            if(vertices[pos] != NULL){
                return vertices[pos];
            }
            return NULL;
		}

		Vertex get_vertex_ref(int pos)
		{
            return *vertices[pos];
		}

		void clear_marks()
		{
			for (int i=0;i<maxVertices;i++)
				marks[i] = false;
		}

		void mark_vertex(Vertex* aVertex)
		{
			int ix = index_is(aVertex);
			marks[ix] = true;
		}
        void change_mark_vertex(Vertex* aVertex){
            int index = index_is(aVertex);
            marks[index] = !marks[index];
        }
        bool isVertexMarked(int pos){
            return marks[pos];
        }
        bool isAnyNotVisited(){
            for(int i = 0; i < nmbVertices; i++){
                if(!marks[i]){
                    return true;
                }
            }
            return false;
        }
		bool is_marked(Vertex* aVertex)
		// Returns true if vertex is marked; otherwise, returns false.
		{
			int index = index_is(aVertex);
            return marks[index];
		}

		Vertex* get_unmarked()
		{
			for (int i=0; i<nmbVertices; i++)
			{
				if (marks[i] == false)
					return vertices[i];
			}
			return NULL;
		}
        int getMinDistance(LinkedList<int>* distancia){
            int aux = 1000000;
            int porRetornar = -1;
            for(int j = 0; j < nmbVertices; j++){
                if(!marks[j]){
                    if(aux>distancia->getElement(j)){
                        aux = distancia->getElement(j);
                        porRetornar = j;
                    }
                }
            }
            return porRetornar;
        }
        LinkedList<int>* getShortestPath(int ini, int fin){
            clear_marks();
            LinkedList<int> distancias;
            LinkedList<int> anteriores;
            LinkedList<int>* solucion = new LinkedList<int>();
            distancias.append(0);
            anteriores.append(UNDEFINED);
            for(int i = 1; i<nmbVertices; i++){
                distancias.append(INFINITE);
                anteriores.append(UNDEFINED);
            }
            while(isAnyNotVisited()){
                int u = getMinDistance(&distancias);
                marks[u] = true;
                LinkedStack<int> posibles = get_neighbors(u);
                LinkedList<int> vecinos;
                while((int)posibles.getSize()>0){
                    vecinos.append(posibles.pop());
                }
                cout << " u= "<< u << endl;
                if(!(u == fin)){
                    int vecino;
                    int auxLength;
                    for(int k = 0; k < vecinos.getSize(); k++)
                    {
                        vecino = vecinos.getElement(k);
                        if(!marks[vecino]){
                            auxLength = weight_is(u,vecino) + distancias.getElement(u);
                            if(auxLength < distancias.getElement(vecino)){
                                distancias.setElement(vecino,auxLength);
                                anteriores.setElement(vecino, u);
                            }
                        }
                    }
                }
                else{
                    cout<< "Se encuentra el elemento final" << endl;
                    while(anteriores.getElement(u) != UNDEFINED){
                        solucion->insert(u);
                        u = anteriores.getElement(u);
                    }
                    solucion->insert(u);
                    break;
                }
            }
            return solucion;
        }
		~Graph()
		{
			for (int i=0;i<nmbVertices;i++)
			{
				delete vertices[i];
			}
		}
};
#endif // GRAPH_INCLUDED
