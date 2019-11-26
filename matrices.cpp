#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

template <class T>
void escribe(string archivo, T* datos1, int n_dat){
  ofstream outfile;
  //abre el archivo.
  outfile.open(archivo);

  for (int i=0; i < n_dat; i++){
    outfile << datos1[i] << endl;
  }
  //cierra el archivo.
  outfile.close(); 
}
template <class T>
void escribe(string archivo, T** datospsi, int pasosx, int pasost){
  ofstream outfile;
  //abre el archivo.
  outfile.open(archivo);

  for (int i=0; i < pasost; i++){
    for (int j=0; j < pasosx; j++){
      outfile << datospsi[i][j] << "\t";
    }
    outfile << endl;
  }
  //cierra el archivo.
  outfile.close(); 
}

void ftcs(float* psin , float* psiv, float deltax, float deltat, int pasost, int pasosx, float D, float s);


int main(){
    float D = 1;
    float s = 1;
    
    float xmin = -1; //En psi 1
    float xmax = 1; //En psi 2
    
    float Nx= 10;
    float variacion = 10;
    float Nxmax = 1000;
    int canti = Nxmax/variacion;
    float *iteraciones = new float[canti];
    float *nxs =  new float[canti];
    int numero = 0;

    for(int n = 10; n< Nxmax; n+=variacion){
        float deltax = (xmax - xmin)/Nx;
        float deltat = deltax*deltax/(2*D);

        bool valor = true;
        
        int pasosx = Nx;
        int pasost = 0;

        while (valor){
            float* psin = new float[pasosx]; //respuesta que quiero
            float* psiv = new float[pasosx]; //respuesta que quiero

            ftcs(psin,psiv, deltax,deltat,pasost,pasosx,D,s);

            float am = abs(psin[0]-psin[1]);

            for(int j = 0; j<pasosx-1; j++){
                float a = psin[j] - psin[j+1];
                if(am < abs(a)){
                    am = abs(a);
                }
            }

            if(am < pow(10, -6)){
                valor = false;
            }
            else{
                pasost += 500;
            }

            delete[] psin;
            delete[] psiv;
        }

        iteraciones[numero] = pasost;
        nxs[numero] = n;
        numero++;
    }
    escribe("iteraciones.txt", iteraciones, numero);
    escribe("nx.txt", nxs, numero);

    return 0;
}

void ftcs(float* psin , float* psiv, float deltax, float deltat, int pasost, int pasosx, float D, float s){
    for(int i = 0; i<pasosx; i++){
        psin[i] = 0;
    }
    for(int j = 0; j < pasosx ; j++){
        psin[j] = psiv[j] + (D*deltat) * (psiv[j+1] - 2*psiv[j] + psiv[j-1])/pow(deltax,2) + deltat*s;
    }
}