It is a simple command line TODO app to better understand the file handling operations in c++. In this app , user can create, view, delete, and update the notes stored in a text file.
The imortant operations in file handling includes: 
1-Writing to a file: ofstream fout("todo.txt", ios::app);
--- ofstream is used to open files in 'write' mode and and fout is ofstream object. ios::app is used to allow append operations to existing file.
2- Reading from file: ifstream fin("todo.txt");
--- instream is used to open files in read mode and allows to read the existing file. 
