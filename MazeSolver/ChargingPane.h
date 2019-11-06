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

class CargarView : public wxDialog
{
    //Declaracion de los atributos y metodos de la ventana de generacion de laberintos
    public:
        CargarView(wxFrame* dlg, const wxString &title);

    protected:
        enum
        {
            idBtnResolver,
            idBtnCargar
        };
    private:
        int getRandomNeighbor(LinkedStack<int> aux, Graph *laberinto);
        int posMatrizALista(int x, int y, int rowSize, int columnSize);
        void OnClose(wxCloseEvent& event);
        void onResolver(wxCommandEvent& evt);
        void onCargar(wxCommandEvent& evt);
        void render(LinkedList<int>* arcos);
        bool cargado;
        wxTextCtrl* numberEntry;
        LinkedList<int>* cargarLaberinto(LinkedList<int>* arcos);
        LinkedList<int>* edges;
        Graph* maze;
        DECLARE_EVENT_TABLE()
    };
    BEGIN_EVENT_TABLE(CargarView, wxDialog)
    EVT_BUTTON(idBtnResolver, CargarView::onResolver)
    EVT_BUTTON(idBtnCargar, CargarView::onCargar)
    END_EVENT_TABLE()

    int CargarView::getRandomNeighbor(LinkedStack<int> aux, Graph *laberinto){
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
    int CargarView::posMatrizALista(int i, int j, int filas, int columnas){
         //Convierte la posicion de una matriz a una lista dados un numero de filas y columnas
        if(i >= columnas || j >= filas || i < 0 || j < 0){
            //cout << "Posicion invalida " << x << " "<< y << endl;
            return -1;
        }
        //cout << "Posicion valida " << x << " "<< y << endl;
        return i + (j*columnas);
    }
    LinkedList<int>* CargarView::cargarLaberinto(LinkedList<int>*arcos){
        //Metodo llamado para pintar un laberinto cargado en memoria.
        Graph* grafo = new Graph(600);
        for(int i = 0; i < 20; i++)
        {
            for(int j = 0; j < 30; j++){
                grafo->add_vertex(new Vertex(j*20,i*20));
            }
        }
        LinkedList<int>* porDibujar = new LinkedList<int>();
        for(int i = 0; i < arcos->getSize()-1; i+=2)
        {
            grafo->add_edge(arcos->getElement(i),arcos->getElement(i+1),1);
            porDibujar->append(arcos->getElement(i));
            porDibujar->append(arcos->getElement(i+1));
        }
        this->edges = porDibujar;
        this->maze = grafo;
        return porDibujar;
    }

    CargarView::CargarView(wxFrame* dlg, const wxString &title)
    : wxDialog(dlg, -1, title)
        {
        //Constructor de la clase que genera los componentes de la ventana.
        this->SetSizeHints(1200, 550);
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
        new wxStaticText(this, wxID_ANY, wxT("Numero de laberinto por cargar:"), wxPoint(700,200), wxDefaultSize, 0);
        wxButton* BtnResolver = new wxButton(this, idBtnResolver, wxT("&Resolver"), wxPoint(1000,300), wxDefaultSize, 0);
        wxButton* BtnCargar = new wxButton(this, idBtnCargar, wxT("&Cargar"), wxPoint(1000,250), wxDefaultSize, 0);
        numberEntry = new wxTextCtrl(this,wxID_ANY,wxEmptyString,wxPoint(1010,200),wxSize(60, wxDefaultCoord),0,wxDefaultValidator,wxTextCtrlNameStr);
        this->SetBackgroundColour(wxColour(* wxWHITE));
        this->SetSizer(sizer);
        this->SetAutoLayout(true);
        sizer->Fit(this);
        srand(time(NULL));
        this->cargado = false;
        }

    void CargarView::OnClose(wxCloseEvent&){
        Destroy();
        }

    void CargarView::render(LinkedList<int>* arcos){
        //Metodo llamado para cargar un laberinto y desplegarlo en pantalla
        LinkedList<int>* porDibujar = cargarLaberinto(arcos);
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
        this->cargado = true;
    }
    void CargarView::onResolver(wxCommandEvent &evt){
        //Metodo que ocurre cuando se llama el boton de resolver, si existe un laberinto generado, se obtiene la ruta mas corta y se dibuja en pantalla
        if(cargado){
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
    void CargarView::onCargar(wxCommandEvent& evt){
        //Metodo encargado de determinar si se inserto un indice valido e invocar el metodo de carga de laberinto.
        int number_of_lines = 0;
        std::string line;
        std::ifstream myfile("LaberintoDB.dat");
        if (myfile){
            while (std::getline(myfile, line))
                ++number_of_lines;
            wxString mazeTemp = numberEntry->GetValue();
            string mazeNumber = string(mazeTemp.mb_str());
            if(mazeNumber.find_first_not_of("0123456789") == string::npos && mazeNumber != "")
            {
                int numberOfMaze = atoi(mazeNumber.c_str());
                if(numberOfMaze <= number_of_lines && numberOfMaze != 0){
                    std::ifstream auxFile("LaberintoDB.dat");
                    while(numberOfMaze > 0){
                        getline(auxFile,line);
                        numberOfMaze--;
                    }
                    std::replace(line.begin(), line.end(), ',', ' ');  // replace ':' by ' '
                    LinkedList<int>* arcos = new LinkedList<int>();
                    stringstream ss(line);
                    int temp;
                    while (ss >> temp)
                        arcos->append(temp);
                    render(arcos);
                }
                else{
                    wxMessageBox(wxT("El laberinto que esta intentando cargar no existe"), wxT("Error al Cargar"), wxICON_INFORMATION);
                    this->cargado = false;
                }
            }
            else{
                wxMessageBox(wxT("El laberinto por cargar debe ser identificado por un numero"), wxT("Error al Cargar"), wxICON_INFORMATION);
                this->cargado = false;
            }

        }
        else{
            wxMessageBox( wxT("Todavia no existen laberintos en memoria."), wxT("Error al Cargar"), wxICON_INFORMATION);
            this->cargado = false;
        }
    }

