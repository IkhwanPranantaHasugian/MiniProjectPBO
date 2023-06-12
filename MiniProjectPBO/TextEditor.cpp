/**************************************************
 * Kelompok 5
 * Ikhwan Prananta Hasugian             (221402004)
 * Ilyaz Al Muadz                       (221402029)
 * Jeconiah Samuel Christian Nababan    (221402069)
***************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

class TextEditor 
{
    private:
        string filename;//Mendeklarasikan variabel 'filename' sebagai string untuk menyimpan nama file.

    public:
        //Constuctor
        TextEditor(string fname)  
        {
            filename = fname;
        }

        //Fungsi Untuk Membuat File 
        void createFile() 
        {
            ofstream file(filename.c_str()); //Membuka File
            file.close();//Menutup File
            cout << "File Berhasil Dibuat: " << filename << endl;
        }
        
        //Fungsi untuk membaca isi file yang telah dibuat dan menampilkannya di layar.
        void readFile() 
        {
            ifstream file(filename.c_str());//Membuka File
            string line;
            cout << "Isi File: " << endl;
            while (getline(file, line)) 
            {
                cout << line << endl;
            }
            file.close(); //Menutup File
        }

        //Fungsi untuk menghapus file yang telah dibuat.
        void deleteFile() 
        {
            if (remove(filename.c_str()) != 0) //Menghapus file dengan menggunakan 'remove()' dan mengembalikan pesan kesalahan jika terjadi kegagalan.
            {
                cerr << "Error Menghapus File." << endl;
            } 
            else 
            {
                cout << "File Berhasil Dihapus: " << filename << endl;
            }
        }

        //Fungsi untuk mengompilasi file dengan menggunakan kompiler 'g++' dan menghasilkan file eksekusi dengan ekstensi '.exe'.
        void compileFile() 
        {
            // Membentuk perintah kompilasi dengan menggunakan nama file yang diberikan.
            string command = "g++ " + filename + " -o " + getFileNameWithoutExtension() + ".exe";
            if (system(command.c_str()) == 0) //Menjalankan perintah kompilasi menggunakan 'system()' dan memeriksa apakah kompilasi berhasil.
            {
                cout << "Compile Berhasil.." << endl;
            } 
            else 
            {
                cerr << "Compile Gagal.." << endl;
            }
        }

        //Fungsi untuk menjalankan file eksekusi yang telah dihasilkan.
        void runExecutable() 
        {
            //Membentuk perintah untuk menjalankan file eksekusi.
            string command =  getFileNameWithoutExtension() + ".exe";
            if (system(command.c_str()) == 0) 
            {
                cout << "Executing Program Berhasil." << endl;
            } 
            else 
            {
                cerr << "Executing Program Gagal." << endl;
            }
        }

        //Fungsi untuk menambahkan baris ke dalam file.
        void addLine(string line) 
        {
            ofstream file(filename.c_str(), ios::app);
            while (line != "selesai") //Looping Penulisan Kalimat Dan Berhenti Ketika User Menuliskan Kata 'Selesai'
            {
                file << line << endl;
                getline(cin, line);
            }
            file.close(); //Menutup File
        }   

        //Fungsi untuk mengedit baris tertentu dalam file dengan mengganti baris tersebut dengan 'newLine'.
        void editLine(int lineNumber, string newLine) 
        {
            ifstream inputFile(filename.c_str());
            ofstream outputFile("temp.txt");
            string line;
            int currentLine = 1;

            while (getline(inputFile, line)) 
            {
                if (currentLine == lineNumber) 
                {
                    outputFile << newLine << endl;
                    cout << "Baris Yang Diedit: " << line << " Menjadi: " << newLine << endl;
                } 
                else 
                {
                    outputFile << line << endl;
                }
                currentLine++;
            }

            inputFile.close();
            outputFile.close();

            remove(filename.c_str());
            rename("temp.txt", filename.c_str());
        }

        //Fungsi Untuk Menghapus Baris Pada File
        void deleteLine(int lineNumber) 
        {
            ifstream inputFile(filename.c_str());
            ofstream outputFile("temp.txt");
            string line;
            int currentLine = 1;

            while (getline(inputFile, line)) 
            {
                if (currentLine != lineNumber) 
                {
                    outputFile << line << endl;
                } else 
                {
                    cout << "Baris Yang Dihapus: " << line << endl;
                }
                currentLine++;
            }

            inputFile.close();
            outputFile.close();

            remove(filename.c_str());
            rename("temp.txt", filename.c_str());
        }

    private:
        //Fungsi privat untuk mendapatkan nama file tanpa ekstensi.
        string getFileNameWithoutExtension() 
        {
            size_t pos = filename.find_last_of(".");
            return filename.substr(0, pos);
        }
};

//Fungsi Utama
int main() 
{
    string filename;

    //Meminta User Untuk Menginput Nama File
    cout << "Masukkan Nama File: ";
    getline(cin, filename);//Membaca nama file yang dimasukkan oleh pengguna.

    TextEditor textEditor(filename); //Membuat objek 'TextEditor' dengan menggunakan nama file yang diberikan.

    int choice;
    // Melakukan perulangan berdasarkan pilihan pengguna sampai pilihan 9 (keluar) dipilih.
    do {
        cout << "\n--- Menu Text Editor  ---" << endl;
        cout << "1. Buat File" << endl;
        cout << "2. Baca File" << endl;
        cout << "3. Hapus File" << endl;
        cout << "4. Compile File" << endl;
        cout << "5. Run Executable" << endl;
        cout << "6. Tambah Text" << endl;
        cout << "7. Edit Baris" << endl;
        cout << "8. Hapus Baris" << endl;
        cout << "9. Keluar Program" << endl;
        cout << "Silahkan Pilih: ";
        cin >> choice; //Membaca pilihan yang dimasukkan oleh pengguna.
        cin.ignore(); //Mengabaikan karakter newline (\n) setelah membaca pilihan agar tidak terbaca sebagai masukan berikutnya.

        //Memeriksa pilihan pengguna dan menjalankan fungsi yang sesuai berdasarkan pilihan user.
        switch (choice) 
        {
            case 1:
                textEditor.createFile();
                break;
            case 2:
                textEditor.readFile();
                break;
            case 3:
                textEditor.deleteFile();
                break;
            case 4:
                textEditor.compileFile();
                break;
            case 5:
                textEditor.runExecutable();
                break;
            case 6: 
            {
                string line;
                cout << "Tuliskan Yang Ingin Anda Tulis (Ketik'selesai' untuk berhenti): " << endl;
                getline(cin, line);
                textEditor.addLine(line);
                break;
            }
            case 7: 
            {
                int lineNumber;
                string newLine;
                cout << "Masukkan Nomor Baris Yang Ingin Di Edit: ";
                cin >> lineNumber;//Meminta User Untuk Menginput Nomor Baris
                cin.ignore();
                cout << "Masukkan Baris Yang Baru: ";
                getline(cin, newLine);//Meminta User Untuk Menginput Baris Baru
                textEditor.editLine(lineNumber, newLine);
                break;
            }
            case 8: 
            {
                int lineNumber;
                cout << "Masukkan Nomor Baris Yang Ingin Dihapus: ";
                cin >> lineNumber;
                cin.ignore();
                textEditor.deleteLine(lineNumber);
                break;
            }
            case 9:
                cout << "Keluar Dari Program..." << endl;
                break;
            default:
                cout << "Pilihan Tidak Sesuai,Coba Lagi..." << endl;
        }
    } while (choice != 9);

    return 0;
}
