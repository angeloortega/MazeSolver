/***************************************************************
 * Name:      DragonView.H
 * Purpose:   Code to display Dragon Curve fractal using
 multiple iterations or a single one
 * Author:    Angelo Ramirez Ortega/Guilliano D' Ambrosio
 * Created:   2017-09-21
 * Copyright: Angelo Ramirez Ortega/Guilliano D' Ambrosio
 * License:
 **************************************************************/
#include "wx/wx.h"
#include "wx/sizer.h"
#include "Programa2App.h"
#include "Programa2Main.h"
#include "LinkedList.h"
#include "Graph.h"
#include <vector>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>

template <typename T>
  std::string NumberToString ( T Number )
  {
    //Convierte un numero a string
     std::ostringstream ss;
     ss << Number;
     return ss.str();
  }

class LaberintoView : public wxDialog
{
    //Declaracion de los atributos y metodos de la ventana de generacion de laberintos
    public:
        LaberintoView(wxFrame* dlg, const wxString &title);

    protected:
        enum
        {
            idBtnRefrescar,
            idBtnResolver,
            idBtnGuardar
        };
    private:
        int getRandomNeighbor(LinkedStack<int> aux, Graph *laberinto);
        int posMatrizALista(int x, int y, int rowSize, int columnSize);
        void OnClose(wxCloseEvent& event);
        void onGenerar(wxCommandEvent& evt);
        void onResolver(wxCommandEvent& evt);
        void onGuardar(wxCommandEvent& evt);
        void render();
        bool generado;
        bool guardado;
        LinkedList<int>* generarLaberinto();
        LinkedList<int>* edges;
        Graph* maze;
        DECLARE_EVENT_TABLE()
    };
    BEGIN_EVENT_TABLE(LaberintoView, wxDialog)
    EVT_BUTTON(idBtnRefrescar, LaberintoView::onGenerar)
    EVT_BUTTON(idBtnResolver, LaberintoView::onResolver)
    EVT_BUTTON(idBtnGuardar, LaberintoView::onGuardar)
    END_EVENT_TABLE()

    int LaberintoView::getRandomNeighbor(LinkedStack<int> aux, Graph *laberinto){
    //obtiene una lista de vecinos y un laberinto, se retorna un vecino aleatorio para la generacion de laberintos
    vector<int> currentNeighbors;
    int auxNum;
    while(aux.getSize() > 0){
        auxNum = aux.pop();
        if(!laberinto->isVertexMarked(auxNum)){
            currentNeighbors.push_back(auxNum);
           }
    }
    if(currentNeighbors.size() > 0){
            int random = rand()%currentNeighbors.size();
            return currentNeighbors[random];
        }
    return -1;
}
    int LaberintoView::posMatrizALista(int i, int j, int filas, int columnas)
    {
        //Convierte la posicion de una matriz a una lista dados un numero de filas y columnas
        if(i >= columnas || j >= filas || i < 0 || j < 0){
            //cout << "Posicion invalida " << x << " "<< y << endl;
            return -1;
        }
        //cout << "Posicion valida " << x << " "<< y << endl;
        return i + (j*columnas);
    }
    LinkedList<int>* LaberintoView::generarLaberinto(){
        //Genera y retorna un laberinto utilando expansion aleatoria de busqueda a profundidad
        int random;
        Graph grafo(600);
        // Crear los Vertices
        // Los vertices contienen un par ordenado, que seran sus cordenadas en pantalla
        for(int i = 0; i < 20; i++)
        {
            for(int j = 0; j < 30; j++){
                grafo.add_vertex(new Vertex(j*20,i*20));
            }
        }
        // Crear los arcos entre los vertices

        int posicionEnArreglo;
        int posicionInicial;
        for(int i = 0;  i < 20; i++){
            for(int j = 0; j<30; j++){
                posicionEnArreglo = posMatrizALista(j+1,i,20,30);
                posicionInicial = posMatrizALista(j, i, 20, 30);
                if(posicionEnArreglo > -1){
                    grafo.add_edge(posicionInicial,posicionEnArreglo,1);
                }
                posicionEnArreglo = posMatrizALista(j,i+1,20,30);
                if(posicionEnArreglo > -1){
                    grafo.add_edge(posicionInicial,posicionEnArreglo,1);
                }
                posicionEnArreglo = posMatrizALista(j-1,i,20,30);
                if(posicionEnArreglo > -1){
                    grafo.add_edge(posicionInicial,posicionEnArreglo,1);
                }
                posicionEnArreglo = posMatrizALista(j,i-1,20,30);
                if(posicionEnArreglo > -1){
                    grafo.add_edge(posicionInicial,posicionEnArreglo,1);
                }
            }
        }
        /*
        forma de grafo actual:
        o-o-o-o-o
        | | | | |
        o-o-o-o-o
        | | | | |
        o-o-o-o-o
        */
        LinkedStack<int> processStack;
        Graph* laberinto = new Graph(600);
        for(int i = 0; i < 20; i++)
        {
            for(int j = 0; j < 30; j++){
                laberinto->add_vertex(new Vertex(j*20,i*20));
            }
        }
        Vertex* current = laberinto->get_vertex(0);
        Vertex* next;
        LinkedList<int>* porDibujar = new LinkedList<int>();
        laberinto->mark_vertex(current);
        int currentPos = 0;
        processStack.push(0);
        while(processStack.getSize() > 0){
            current = laberinto->get_vertex(currentPos);
            LinkedStack<int> currentNeighbors = grafo.get_neighbors(currentPos);
            random = getRandomNeighbor(currentNeighbors,laberinto);
            if(random > -1){
                next = laberinto->get_vertex(random);
                laberinto->add_edge(currentPos,random,1);
                laberinto->mark_vertex(next);
                processStack.push(currentPos);
                porDibujar->append(currentPos);
                porDibujar->append(random);
                currentPos = random;

            }
            else{
                currentPos = processStack.pop();
            }
        }
        this->edges = porDibujar;
        this->maze = laberinto;
        return porDibujar;
    }

    LaberintoView::LaberintoView(wxFrame* dlg, const wxString &title)
    : wxDialog(dlg, -1, title)
        {
        //Constructor de la clase que genera los componentes de la ventana.
        this->SetSizeHints(1000, 550);
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
        wxButton* BtnRefrescar = new wxButton(this, idBtnRefrescar, wxT("&Generar"), wxPoint(780,200), wxDefaultSize, 0);
        wxButton* BtnResolver = new wxButton(this, idBtnResolver, wxT("&Resolver"), wxPoint(780,250), wxDefaultSize, 0);
        wxButton* BtnGuardar = new wxButton(this, idBtnGuardar, wxT("&Guardar"), wxPoint(780,300), wxDefaultSize, 0);
        this->SetBackgroundColour(wxColour(* wxWHITE));
        this->SetSizer(sizer);
        this->SetAutoLayout(true);
        sizer->Fit(this);
        srand(time(NULL));
        this->generado = false;
        this->guardado = false;
        }

    void LaberintoView::OnClose(wxCloseEvent&){
        Destroy();
        }
    void LaberintoView::render(){
        //Genera un laberinto aleatorio y mediante la lista de arcos obtenida, se despliega en pantalla.
        LinkedList<int>* porDibujar = generarLaberinto();
        LinkedList<Vertex*> vertices = this->maze->getVertices();
        wxClientDC draw(this);
        Vertex* ini;
        Vertex* fin;
        draw.SetBrush(*wxBLACK_BRUSH);
        draw.SetPen( wxPen(wxColor(255,255,255),5));
        draw.DrawRectangle( 35, 35, 610, 410 );
        draw.SetPen( wxPen( wxColor(255, 255, 255),8) );
        for(int i= 0; i<porDibujar->getSize()-1; i+=2){
            ini = vertices.getElement(porDibujar->getElement(i));
            fin = vertices.getElement(porDibujar->getElement(i+1));
            draw.DrawLine(ini->x + 50, ini->y + 50, fin->x + 50, fin->y+ 50);
            }
        draw.SetPen( wxPen(wxColor(0,0,255),15));
        draw.DrawPoint(48,48);
        draw.SetPen( wxPen(wxColor(255,0,0),15));
        draw.DrawPoint(630,430);
    }
    void LaberintoView::onGenerar(wxCommandEvent &evt){
        //Despliega el laberinto en pantalla y cambia las banderas de generado y guardado
        render();
        this->generado = true;
        this->guardado = false;
    }
    void LaberintoView::onResolver(wxCommandEvent &evt){
        //Metodo que ocurre cuando se llama el boton de resolver, si existe un laberinto generado, se obtiene la ruta mas corta y se dibuja en pantalla
        if(generado){
        LinkedList<int>* solucion = this->maze->getShortestPath(0,599);
        wxClientDC draw(this);
        LinkedList<Vertex*> vertices = this->maze->getVertices();
        draw.SetPen( wxPen( wxColor(0, 0, 255),8) );
        Vertex* ini;
        Vertex* fin;
        for(int i= 0; i<solucion->getSize()-1; i+=1){
            draw.SetPen( wxPen( wxColor(0+i, 0, 255-i),8));
            ini = vertices.getElement(solucion->getElement(i));
            fin = vertices.getElement(solucion->getElement(i+1));
            draw.DrawLine(ini->x + 50, ini->y + 50, fin->x + 50, fin->y+ 50);
            }
        }
        else{
            wxMessageBox( wxT("Primero se debe generar un laberinto."), wxT("Error al tratar de resolver"), wxICON_INFORMATION);
        }
    }
    void LaberintoView::onGuardar(wxCommandEvent& evt){
        //determina si el laberinto ya fue guardado o generado, se coloca la lista de arcos en forma de string al final del archivo LaberintoDB.dat
        if(!guardado){
            if(generado){
                std::ofstream outfile;
                string outString("");
                outfile.open("LaberintoDB.dat", ios_base::app);
                for(int i=0; i < this->edges->getSize(); i++){
                    outString += NumberToString(this->edges->getElement(i));
                    if(i + 1 != this->edges->getSize()){
                        outString +=(string) ",";
                }
                outString += (string) "\n";
                outfile << outString.c_str();
                outfile.close();
                int number_of_lines = 0;
                std::string line;
                std::ifstream myfile("LaberintoDB.dat");
                while (std::getline(myfile, line))
                    ++number_of_lines;
                string message("Se guardo el laberinto #");
                message += NumberToString(number_of_lines);
                const char *outMessage = message.c_str();
                wxMessageBox( outMessage, wxT("Guardado con exito"), wxICON_INFORMATION);
                this->guardado = true;
            }
            else{
                wxMessageBox( wxT("Primero se debe generar un laberinto."), wxT("Error al tratar de guardar"), wxICON_INFORMATION);

            }
        }
        else{
            wxMessageBox( wxT("El laberinto ya fue guardado"), wxT("Error al tratar de guardar"), wxICON_INFORMATION);
        }
    }

