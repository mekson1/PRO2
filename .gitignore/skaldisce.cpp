#include<iostream>	//  knjiznice
#include<fstream>	//	ofstream = pisanje v datoteko; ifstream = branje iz datoteke; fstream = oboje 
#include<string>	// delo z nizi
#include<stdlib.h> 
using namespace std;

class kljuc
{
	string kljuc;
		public:
			void vnosk();
};

class upravljanje		// razred upravljanje
{
  public:      			// javne metode
    void vnos();		
    void izpis();		
    int vsota();		
    void sum_naziv();	
};

void kljuc::vnosk()
{
	string kljuc;
	    cout << "kljuc: ";
	    cin >> kljuc;
	    system("cls");
	    if(kljuc=="test"){
	            cout << "Pravilen kljuc. Dostop omogocen."<<endl<<endl;
	            		}
	        else{
	            cout << "Dostop onemogocen."<<endl;
	    		cout << "Napacen kljuc.";
  		exit (0);
	            }		
}

void upravljanje::vnos()		// metoda za vnos
{	
    string a,b;    //niz
    float c;
	ofstream file;
	
    file.open("skladisce.txt", ios::app);	//odpremo ali ustvarimo datoteko v katero dodajamo (ios::app)	
	cout<<"Vnesi id: ";
	cin>>a;
	
    ifstream datoteka_id("skladisce.txt");
	string line;
    bool obstaja = false;    	
	string aa = a + " ";		//dodamo presledek, ce iscemo 1 da ne dobimo 11
	
    while(getline(datoteka_id, line))  //beremo vrstico za vrstico
    {              
        if(line.find(aa) < line.size())		//v dolzini niza line najdemo niz aa
        {
            obstaja = true;			//zabelezimo najdbo
            string presl = " ";		//presledek, ki ga bomo iskali
            int pos;
            int od = 0;
            int i = 1;
            string novi_vnos = line;           
           	
            while(i < line.size()) 
            {
                pos = line.find(presl, od);		//shranimo indeks, kjer najdemo presledek
                if(i == 2)		//iscemo drugi presledek
                {
                     break; 	//izstopimo ven iz while, ce smo ga nasli
                }
                od = pos + 1; 	//shranimo indeks od koder nadaljujemo iskanje
                ++i;	//stejemo presledke
            }            
            
            novi_vnos.erase(pos, line.size());	//izbrisemo od drugega presledka dalje do velikosti niza
            a = novi_vnos;		//shranimo id in naziv v niz a
        }
    }
    
    if(obstaja)		//ce artikel obstaja
    {		do{cout<<"Artikel obstaja: "<<a<<endl<<"Vnesi kolicino(+/-(10)): ";    
        	cin>>c;}
			while(c<-10||c>10);
        file <<a + " "<<c<<endl; 
        file.close(); 
    }
   	else		//ce artikel ne obstaja
    {
        file <<a<<" ";
    	cout<<"Vnesi naziv: ";
    	cin>>b;
    	file <<b<<" ";
    		do{cout<<"Vnesi kolicino(+/-(10)): ";
    		cin>>c;}
    		while(c<-10||c>10);
    	file <<c<<endl;
    	file.close();        
    }
}
 
void upravljanje::izpis()
{
    ifstream file;	// beremo iz datoteke
    int id;
    string naziv;
    int kol;
    
	file.open("skladisce.txt");		// odpremo datoteko
	
    while(file>>id>>naziv>>kol)		
    {
		cout<<id<<" "<<naziv<<" "<<kol<<" "<<endl; // izpise vrstice
    }
	file.close();		//zapremo datoteko
}
 
int upravljanje::vsota()
{
    ifstream file;
    int id;
    string naziv;
    int kol=0;
    int a=0;
    
	file.open("skladisce.txt");
	
    while(file>>id>>naziv>>kol)
    {
		a +=kol;
    }
	
    file.close();
    return a;	// vrne skupno kolicino
}
 
void upravljanje::sum_naziv()
{
    ifstream file;
    int id;
    string naziv;
    int kol=0;
    int sum=0;
    string iskani_naziv;
    
	cout<<"Vnesi naziv: ";
	cin>>iskani_naziv;
	file.open("skladisce.txt");

	while(file>>id>>naziv>>kol)
	{
        if(iskani_naziv==naziv)	//primerja naziv
		{	
			sum +=kol;			// sesteje
		}
    }

	cout<<iskani_naziv<<": "<<sum<<endl;
	file.close();	
}


int main ()			// glavna funkcija
{	
	kljuc vpis;		// objekt vpis
	vpis.vnosk();	// klic funkcije
		
    upravljanje upr;		// objekt upr
    
    int  v;			// deklaracija spremenjlivke
    char izbira;    //znak za izbiro	
    
	do   //izvajaj ...
	{
        cout<<endl;		// nova vrstica
		cout<<"Skladisce - izbira: " <<endl;	// izpis
		cout<<"1 Vnos(+/-)"<<endl;
		cout<<"2 Izpis "<<endl;
		cout<<"3 Stevilo vseh artiklov v skladiscu"<<endl;
		cout<<"4 Stevilo artiklov v skladiscu po nazivu"<<endl;
		cout<<"0 Izhod"<<endl;
		cout<<endl;
		cout<<"Vasa izbira: ";
		cin>> izbira;       //vnos znaka za izbiro
		cout<<endl;
		switch(izbira)      //krmiljenje glede na izbiro
		{
			case '1':       //v primeru da smo izbrali 1
			{
                cout<<"Vnos(+/-):"<<endl;		  
                upr.vnos();  //klic funkcije
				break;
			}
			case '2':       //v primeru da smo izbrali 2
			{ 
			    cout<<"Zaloga skladisca:"<<endl;
                cout<<"ID; NAZIV; KOLICINA"<<endl;
            	upr.izpis();   //klic funkcije
				break;
			}
			case '3':		//v primeru da smo izbrali 3
			{
			    cout<<"Stevilo vseh artiklov v skladiscu: ";
				v=upr.vsota();	// klic funkcije
				cout<<"vsota: "<<v<<endl;
				break;
			}
			case '4':       //v primeru da smo izbrali 4
			{
			    cout<<"Stevilo artiklov v skladiscu po nazivu:"<<endl; 
            	upr.sum_naziv();   //klic funkcije
				break;
			}
			case '0':		//v primeru da smo izbrali 0
			{
				cout<<"Hvala ker uporabljate nas program.";
				return 0;			
            }
			default : cout<<"Ups, izbrali ste neobstojeco ali napacno moznost"<<endl;
		}
	}
	while(izbira != '0');       //... dokler ne izberemo 0
    
    return 0;
}
