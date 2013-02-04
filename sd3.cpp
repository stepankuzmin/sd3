#include <fstream>
#include <iostream>
using namespace std;

int main() {
  // File headers
  int version;
  int datarate;
  int samples_count;
  int mode;
  int address;
  int date;
  int time;
  int x_source;
  int y_source;
  int h_source;
  
  // Record headers
  int x_state;
  int y_state;
  int z_state;
  int x_incl;
  int y_incl;
  int z_incl;
  int x;
  int y;
  int h;


  FILE *file;
  file = fopen("121128-073403.sd3", "rb");

  // skeep file header
  // fseek(file, 40, SEEK_SET);

  // Header
  fread(&version,         sizeof(int), 1, file);
  fread(&datarate,        sizeof(int), 1, file);
  fread(&samples_count,   sizeof(int), 1, file);
  fread(&mode,            sizeof(int), 1, file);
  fread(&address,         sizeof(int), 1, file);
  fread(&date,            sizeof(int), 1, file);
  fread(&time,            sizeof(int), 1, file);
  fread(&x_source,        sizeof(int), 1, file);
  fread(&y_source,        sizeof(int), 1, file);
  fread(&h_source,        sizeof(int), 1, file);

  cout << "=== HEADER ===\n";
  cout << "version: "  << version << '\n';
  cout << "datarate: " << datarate << '\n';
  cout << "samples: "  << samples_count << '\n';
  cout << "mode: "     << mode << '\n';
  cout << "address: "  << address << '\n';
  cout << "date: "     << date << '\n';
  cout << "time: "     << time << '\n';
  cout << "x_source: " << x_source << '\n';
  cout << "y_source: " << y_source << '\n';
  cout << "h_source: " << h_source << '\n';

  // Records
  int j=0;
  float X[samples_count], Y[samples_count], Z[samples_count];
  while (!feof(file)) {

    // Skeep record header
    // fseek(file, 40, SEEK_CUR);

    // Record
    fread(&x_state, sizeof(int), 1, file);
    fread(&y_state, sizeof(int), 1, file);
    fread(&z_state, sizeof(int), 1, file);

    fread(&x_incl, sizeof(int), 1, file);
    fread(&y_incl, sizeof(int), 1, file);
    fread(&z_incl, sizeof(int), 1, file);

    fread(&x, sizeof(int), 1, file);
    fread(&y, sizeof(int), 1, file);
    fread(&h, sizeof(int), 1, file);

    // Reserved
    fseek(file, sizeof(int), SEEK_CUR);

    cout << "\n=== RECORD " << ++j << " HEADER ===\n";
    cout << "x_state: "  << x_state << '\n';
    cout << "y_state: "  << y_state << '\n';
    cout << "z_state: "  << z_state << '\n';
    cout << "x_incl: "  << x_incl << '\n';
    cout << "y_incl: "  << y_incl << '\n';
    cout << "z_incl: "  << z_incl << '\n';
    cout << "x: "  << x << '\n';
    cout << "y: "  << y << '\n';
    cout << "h: "  << h << '\n';


    // Record X
    for (int i=0; i<samples_count; i++) {
      fread(&X[i], sizeof(float), 1, file);
    }

    cout << "\n=== RECORD X ===\n";
    for (int i=0; i<=8; i++) {
      cout << X[i] << " ";
    }

    // Record Y
    for (int i=0; i<samples_count; i++) {
      fread(&Y[i], sizeof(float), 1, file);
    }

    cout << "\n=== RECORD Y ===\n";
    for (int i=0; i<=8; i++) {
      cout << Y[i] << " ";
    }

    // Record Z
    for (int i=0; i<samples_count; i++) {
      fread(&Z[i], sizeof(float), 1, file);
    }

    cout << "\n=== RECORD Z ===\n";
    for (int i=0; i<=8; i++) {
      cout << Z[i] << " ";
    }
    cout << "\n\n\n";
  }
  fclose(file);

  return 0;
}
