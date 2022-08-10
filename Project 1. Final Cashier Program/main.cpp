#include <iostream>
#include <string>
#include <iomanip>
#include <array>
#include <vector>

using namespace std;

void input_data(array<int, 100>& jumlah, array<int, 100>& harga, array<string, 100>& nama_barang, array<int, 100>& total, int& input_index)
{
    cout << "Masukkan barang ke-" << input_index + 1 << '\n';
    cout << "Nama barang: ";
    cin >> nama_barang[input_index];

    int duplikasi{0};

    for(int j = 0; j < input_index ; j = j + 1)
    {
        if(nama_barang[input_index] == nama_barang[j])
        {
            nama_barang[input_index] = "void";
            input_index = input_index - 1; //Supaya input_index tidak naik, sehingga daftar barang tetap konsisten.

            duplikasi = 1;
            cout << "Maaf, barang ini merupakan duplikat \n\n";
        }
    }

    if(duplikasi == 1)
    {
        return;
    }
    else
    {
        cout << "Jumlah barang: ";
        cin >> jumlah[input_index];

        cout << "Harga barang: ";
        cin >> harga[input_index];

        //So the total price is the amount * price
        total[input_index] = jumlah[input_index] * harga[input_index];
    }
}

void lihat_kuitansi(array<int, 100>& jumlah, array<int, 100>& harga, array<string, 100>& nama_barang, array<int, 100>& total, int input_index, int total_semua)
{
    //Kuitansi belanja
    cout << "================";
    cout << "\nCatatan Belanja\n";
    cout << "================";

    cout << "\n";
    cout << "No   Barang   Jumlah   Harga   Total";
    cout << "\n";

    //setw sets the "field width"
    for(int i = 0; i < input_index; i = i + 1)
    {
        cout << setw(2) << i + 1 << setw(9) << nama_barang[i] << setw(9) << jumlah[i] << setw(8) << harga[i] << setw(8) << total[i] << '\n';
    }
    cout << "------------------------------------------ + \n";
    cout << setw(36) << total_semua << '\n';
}

void delete_barang(array<int, 100>& jumlah, array<int, 100>& harga, array<string, 100>& nama_barang, array<int, 100>& total, int jumlah_barang, int& total_semua, int barang_del)
{
    total_semua = total_semua - total[barang_del];
    for(int i = barang_del ; i < 99 ; i = i + 1)
    {
        nama_barang[i] = nama_barang[i + 1];
        harga[i] = harga[i + 1];
        jumlah[i] = jumlah[i + 1];
        total[i] = total[i + 1];
    }
}

void bayar_barang(int total_semua)
{
    int diskon{};
    int bayar{};

    if(total_semua >= 100000)
    {
        diskon = 0.06*total_semua;
    }
    else if(total_semua >= 50000)
    {
        diskon = 0.04*total_semua;
    }
    else if(total_semua >= 25000)
    {
        diskon = 0.02*total_semua;
    }
    else
    {
        diskon = 0;
    }

    //conclusion
    cout << "Jumlah bayar: " << total_semua << '\n';
    cout << "Diskon: " << diskon << '\n';
    cout << "Total bayar: " << total_semua - diskon << '\n';
    while(bayar < total_semua - diskon)
    {
        cout << "Bayar: ";
        cin >> bayar;
    }
    cout << "Kembalian: " << (bayar - (total_semua - diskon)) << '\n';
}

int main()
{
    bool flag{1};
    int index_item{}; //Item ke berapa?
    int bayar{};
    int diskon{};
    array<int, 100> jumlah{};
    array<int, 100> harga{};
    array<int, 100> total{};
    int total_semua{};
    array<string, 100> nama_barang{};
    bool duplikasi_item{};
    int pilihan{}; //1. Input, 2. Lihat daftar, 3. Delete , 4. Bayar

    while(flag)
    {
        cout << "=========================\n";
        cout << "Kasir Sederhana ala Leon \n";
        cout << "=========================\n\n";

        //Ada 4 pilihan, pilih yang mana?
        cout << "Apakah anda mau: 1. Input data barang, 2. Lihat daftar barang, 3. Delete daftar barang, atau 4. Bayar ? \n";
        cout << "Pilih antara 1/2/3/4 : ";
        cin >> pilihan;

        if(pilihan == 1)
        {
            input_data(jumlah, harga, nama_barang, total, index_item);
            total_semua = total_semua + total[index_item];
            index_item = index_item + 1;

        }
        else if(pilihan == 2)
        {
            lihat_kuitansi(jumlah, harga, nama_barang, total, index_item, total_semua);
        }
        else if(pilihan == 3)
        {
            int barang_del{};
            string nama_barang_delete{};
            lihat_kuitansi(jumlah, harga, nama_barang, total, index_item, total_semua);
            cout << "Pilih barang yang ingin anda delete: ";
            cin >> nama_barang_delete;
            for(int i = 0; i < index_item; i = i + 1)
            {
                if(nama_barang_delete == nama_barang[i])
                {
                    int barang_del{i};
                    delete_barang(jumlah, harga, nama_barang, total, index_item, total_semua, barang_del);

                    index_item = index_item - 1;
                }
            }

            cout << '\n' << '\n' ;

            lihat_kuitansi(jumlah, harga, nama_barang, total, index_item, total_semua);
        }
        else if(pilihan == 4)
        {
            bayar_barang(total_semua);
            break;
        }

        cout << "\n\n";
    }

    return 0;
}
