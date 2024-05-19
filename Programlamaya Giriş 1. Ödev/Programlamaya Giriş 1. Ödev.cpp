
#include <iostream>
#include <time.h>
#include <iomanip>
#include <stdlib.h>
#include <locale.h>
#include <math.h>


using namespace std;

//30 ad ve soyad içeren diziler tanımladım.
string Adlar[30] = { "Ahmet","İlber","Yavuz","Mustafa","Yusuf","Ali","Zülfikar","Uğur","Metin","Süleyman","Bolat","Talha","Kadir","Mertcan","Özgür","Ayşenur","Gökçe","Zeynep","Zehra","Zümra","Aslı","Belgin","Selin","Rümeysa","Sude","Kadriye","Müyesser","Seyra","Melike","Ceren" };
string Soyadlar[30] = { "Gündüz","Karahan","Haliloğlu","Güler","Kaya","Gece","Tuzcu","Kar","Ülker","Ortaylı","Yılmaz","Dağ","Kitapcı","Danacı","Altuındağ","Gencay","Kuşçu","Atalar","Çelebi","Albak","Türk","Gün","Yoluaçık","Dengiyok","Karabağlamış","Demirci","Aydan","Suakıtıcı","Güneybaz","Huysuz" };

//içinde gerekli bilgiler olan struct oluşturdum.
struct bilgi
{
	string ad;
	string soyad;
	int kisa_sinav1;
	int kisa_sinav2;
	int odev1;
	int odev2;
	int proje;
	int vize;
	int final;
	int basari_puan;
	string harf_puan;
};

//structı kullanarak 100 öğrencilik dizi oluşturdum
bilgi ogr[100];

//en yüksek ve en düşük değerin belirlenmesi için 4 tane değer oluşturdum.
int enyuksek = 0;
int endusuk = 100;
string ey_ad;
string ed_ad;

//basarı ortalamasını almak içine int oluşturdum.
double basari_ort = 0;

//Standart sapmayı almak için başarı ortalamalarını depolayacak varyans ve bunu heaplarla yazdırabilecek standrart sapma tanımladım.
double varyans[100];
double standart_sapma;

//En sonda oluşturduğum fonksiyonları üstte tanımladım.
void Basliklar();
void Devam(int bas, int son);
void Notlar(int bas, int son, int bolen, int ara);
int Kontrol(int sayi);



int main()
{
	//Türkçe karakterleri tanıması için.
	setlocale(LC_ALL, "Turkish");

	//rastgele değerler vermesi için.
	srand(time(NULL));

	//Kendisinin mi bir değer atamasını toksa random mu alınmasını istediğini sordum.
	int tus;
	cout << "Kendin değer girmek istiyorsan [1] tuşla" << endl;
	cout << "Rastgele atanmasını istiyorsan [0] tuşla" << endl;
	cin >> tus;

	//1 i tuşlarsa değer isteyecek
	if (tus == 1) {
		int i;
		cout << "Notları 0 ile 100 arasında giriniz,aksi takdirde işlem sonlanacaktır" << endl;
		for (i = 1; i <= 100; i++) {
			//Sırayla 100 tane structaki değerleri aldım.
			bilgi dizi;
			cout << i << ". Öğrencinin adı:" << endl;
			cin >> dizi.ad;
			cout << i << ". Öğrencinin Soyadı:" << endl;
			cin >> dizi.soyad;
			cout << i << ". Öğrencinin 1. kısa sınav notu:" << endl;
			//100 den küçük ve 0 dan büyük mü diye kontrol fonksiyonunu ekledim.
			cin >> dizi.kisa_sinav1;
			Kontrol(dizi.kisa_sinav1);
			cout << i << ". Öğrencinin 2. kısa sınav notu:" << endl;
			cin >> dizi.kisa_sinav2;
			Kontrol(dizi.kisa_sinav2);
			cout << i << ". Öğrencinin 1. ödev notu:" << endl;
			cin >> dizi.odev1;
			Kontrol(dizi.odev1);
			cout << i << ". Öğrencinin 2. ödev notu:" << endl;
			cin >> dizi.odev2;
			Kontrol(dizi.odev2);
			cout << i << ". Öğrencinin proje notu:" << endl;
			cin >> dizi.proje;
			Kontrol(dizi.proje);
			cout << i << ". Öğrencinin vize notu:" << endl;
			cin >> dizi.vize;
			Kontrol(dizi.vize);
			cout << i << ". Öğrencinin final notu:" << endl;
			cin >> dizi.final;
			Kontrol(dizi.final);
			dizi.basari_puan = (dizi.vize * 1 / 2 + dizi.kisa_sinav1 * 7 / 100 + dizi.kisa_sinav2 * 7 / 100 + dizi.odev1 * 1 / 10 + dizi.odev2 * 1 / 10 + dizi.proje * 16 / 100) * 55 / 100 + dizi.final * 45 / 100;

			//Basarı ortalamasını hesapladım.
			basari_ort += dizi.basari_puan;
			//Basarı notlarını diziye ekledim.
			varyans[i] = dizi.basari_puan;

			//En yüksek not değerini buldum.
			if (dizi.basari_puan > enyuksek) {
				enyuksek = dizi.basari_puan;
				ey_ad = dizi.ad + " " + dizi.soyad;
			}

			//En düşük not değerini buldum.
			if (dizi.basari_puan < endusuk) {
				endusuk = dizi.basari_puan;
				ed_ad = dizi.ad + " " + dizi.soyad;
			}

			//1 öğrenciyi ogr dizisine ekledim
			ogr[i] = dizi;

		}
		cout << endl;
		//Fonksiyonları ekledim.
		Basliklar();
		Devam(1, 100);

		//en düşük not,en yüksek not ve sınıfın başarı ortalamasını yazdırdım.
		cout << "\nEn yüksek not:" << enyuksek
			<< "\nNotun sahibi:" << ey_ad << endl;

		cout << "En düşük not:" << endusuk
			<< "\nNotun sahibi:" << ed_ad << endl;

		cout << "Sınıfın başarı ortalaması:" << basari_ort / 100 << endl;

		//Standart sapmayı hesaplayuıp yazdırdım.
		for (int i = 1; i <= 100; i++)
			standart_sapma += pow(varyans[i], 2);
		standart_sapma = sqrt(standart_sapma / (basari_ort - 1));

		cout << "Standart sapma:" << standart_sapma << endl;

		//Notu belirli bir aralıkta olan kişileri dizilerden çekip yazdırdım.
		cout << "Notu 50 ile 80 arası olanlar:" << endl;
		for (int i = 1; i <= 100; i++) {
			if (ogr[i].basari_puan < 80 && ogr[i].basari_puan >50)
				cout << ogr[i].ad + " " + ogr[i].soyad + ",";
		}
		cout << endl;

		cout << "Notu 70'den fazla olanlar:" << endl;
		for (int i = 1; i <= 100; i++) {
			if (ogr[i].basari_puan > 70)
				cout << ogr[i].ad + " " + ogr[i].soyad + ",";
		}
		cout << endl;

		cout << "Notu 70'den az olanlar:" << endl;
		for (int i = 1; i <= 100; i++) {
			if (ogr[i].basari_puan < 70)
				cout << ogr[i].ad + " " + ogr[i].soyad + ",";
		}
		return 0;
	}
	//0 ı tuşlarsa rastgele değerler atama.
	else if (tus == 0) {
		//Fonksiyonlar.
		Basliklar();

		Notlar(1, 10, 40, 0);
		Notlar(11, 60, 30, 40);
		Notlar(61, 75, 10, 70);
		Notlar(76, 100, 20, 80);

		//en düşük not,en yüksek not ve sınıfın başarı ortalamasını yazdırdım.
		cout << "\nEn yüksek not:" << enyuksek
			<< "\nNotun sahibi:" << ey_ad << endl;

		cout << "En düşük not:" << endusuk
			<< "\nNotun sahibi:" << ed_ad << endl;

		cout << "Sınıfın başarı ortalaması:" << basari_ort / 100 << endl;

		//Standart sapmayı hesaplayuıp yazdırdım.
		for (int i = 1; i <= 100; i++)
			standart_sapma += pow(varyans[i], 2);
		standart_sapma = sqrt(standart_sapma / (basari_ort - 1));

		cout << "Standart sapma:" << standart_sapma << endl;

		//Notu belirli bir aralıkta olan kişileri dizilerden çekip yazdırdım.
		cout << "Notu 50 ile 80 arası olanlar:" << endl;
		for (int i = 1; i <= 100; i++) {
			if (ogr[i].basari_puan < 80 && ogr[i].basari_puan >50)
				cout << ogr[i].ad + " " + ogr[i].soyad + ",";
		}
		cout << endl;

		cout << "Notu 70'den fazla olanlar:" << endl;
		for (int i = 1; i <= 100; i++) {
			if (ogr[i].basari_puan > 70)
				cout << ogr[i].ad + " " + ogr[i].soyad + ",";
		}
		cout << endl;

		cout << "Notu 70'den az olanlar:" << endl;
		for (int i = 1; i <= 100; i++) {
			if (ogr[i].basari_puan < 70)
				cout << ogr[i].ad + " " + ogr[i].soyad + ",";
		}
		return 0;
	}

	//0 veya 1 girilmezse program biticek.
	else {
		cout << "!!Bilinmeyen seçenek!!" << endl;
		return 0;
	}
}


//Rastgele notları atayacak fonksiyon oluşturdum.
void Notlar(int bas, int son, int bolen, int ara) {


	for (int i = bas; i <= son; i++) {

		//fonksiyonları belirlenen değerler arrasında rastgele atadım.
		bilgi dizi;
		dizi.ad = Adlar[rand() % 30];
		dizi.soyad = Soyadlar[rand() % 30];
		dizi.kisa_sinav1 = rand() % bolen + ara;
		dizi.kisa_sinav2 = rand() % bolen + ara;
		dizi.odev1 = rand() % bolen + ara;
		dizi.odev2 = rand() % bolen + ara;
		dizi.proje = rand() % bolen + ara;
		dizi.vize = rand() % bolen + ara;
		dizi.final = rand() % bolen + ara;
		dizi.basari_puan = (dizi.vize * 1 / 2 + dizi.kisa_sinav1 * 7 / 100 + dizi.kisa_sinav2 * 7 / 100 + dizi.odev1 * 1 / 10 + dizi.odev2 * 1 / 10 + dizi.proje * 16 / 100) * 55 / 100 + dizi.final * 45 / 100;

		//Basarı ortalamasını hesapladım.
		basari_ort += dizi.basari_puan;
		//Basarı notlarını diziye ekledim.
		varyans[i] = dizi.basari_puan;

		//En yüksek not değerini buldum.
		if (dizi.basari_puan > enyuksek) {
			enyuksek = dizi.basari_puan;
			ey_ad = dizi.ad + " " + dizi.soyad;
		}

		//En düşük not değerini buldum.
		if (dizi.basari_puan < endusuk) {
			endusuk = dizi.basari_puan;
			ed_ad = dizi.ad + " " + dizi.soyad;
		}
		ogr[i] = dizi;
	}
	Devam(bas, son);
};

//Değerleri yazdıracak fonksiyon oluşturdum.
void Devam(int bas, int son)
{
	for (int i = bas; i <= son; i++) {

		//Seçilen numaralar arasındaki değerleri yazdırdım.
		cout << setw(5) << i
			<< left << setw(15) << ogr[i].ad
			<< left << setw(20) << ogr[i].soyad
			<< left << setw(15) << ogr[i].kisa_sinav1
			<< left << setw(15) << ogr[i].kisa_sinav2
			<< left << setw(15) << ogr[i].odev1
			<< left << setw(15) << ogr[i].odev2
			<< left << setw(15) << ogr[i].proje
			<< left << setw(15) << ogr[i].vize
			<< left << setw(15) << ogr[i].final
			<< left << setw(15) << ogr[i].basari_puan << setw(10);

		//başarı notunu harfe çevirme yazdım.

		if (ogr[i].basari_puan <= 100 && ogr[i].basari_puan >= 88)
			cout << left << setw(12) << "AA";
		else if (ogr[i].basari_puan < 88 && ogr[i].basari_puan >= 81)
			cout << left << setw(12) << "BA";
		else if (ogr[i].basari_puan < 81 && ogr[i].basari_puan >= 74)
			cout << left << setw(12) << "BB";
		else if (ogr[i].basari_puan < 74 && ogr[i].basari_puan >= 67)
			cout << left << setw(12) << "CB";
		else if (ogr[i].basari_puan < 67 && ogr[i].basari_puan >= 60)
			cout << left << setw(12) << "CC";
		else if (ogr[i].basari_puan < 60 && ogr[i].basari_puan >= 53)
			cout << left << setw(12) << "DC";
		else if (ogr[i].basari_puan < 53 && ogr[i].basari_puan >= 46)
			cout << left << setw(12) << "DD";
		else if (ogr[i].basari_puan < 46 && ogr[i].basari_puan >= 39)
			cout << left << setw(12) << "FD";
		else cout << left << setw(12) << "FF";

		cout << rand() % 30 << "/" << rand() % 12 + 1 << "/" << rand() % 5 + 2000 << endl;

		//20 öğrencide bir silip devamını yazacak programı yazdım.
		if (i == 20 || i == 40 || i == 60 || i == 80) {
			cout << "Devam etmek için [D] tuşuna basınız" << endl;
			char D;
			cin >> D;
			if (D == 'd' || D == 'D') {
				system("CLS");
				Basliklar();
			}
			else
				exit(0);
		}
	}

};

//Bizden değerleri isteyen fonksiyonu tanımladım.
void Basliklar() {

	//Tablodaki ana isimleri yazdırdım.
	cout << left << setw(7) << "Sıra"
		<< left << setw(13) << "Adı"
		<< left << setw(16) << "Soyadı"
		<< left << setw(15) << "Kısa Sınav 1"
		<< left << setw(17) << "Kısa Sınav 2"
		<< left << setw(15) << "Ödev 1"
		<< left << setw(15) << "Ödev 2"
		<< left << setw(15) << "Proje"
		<< left << setw(15) << "Vize"
		<< left << setw(13) << "Final"
		<< left << setw(15) << "Başarı Notu"
		<< left << setw(15) << "Harfen Puan"
		<< left << setw(15) << "Doğum Tarihi" << endl;
};

//Kullanıcının girdiği değerin doğru aralıktamı olduğunu kontrol eden fonskiyon oluşturdum.
int Kontrol(int sayi) {
	if (sayi < 0 || sayi>100)
		exit(0);
};