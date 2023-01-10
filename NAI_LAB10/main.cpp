#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include <opencv2/core/types.hpp>

using namespace cv;
using namespace std;

int main(){
//    Ustawienie parametrów ArUco
Ptr<aruco::Dictionary> dictionary = aruco::getPredefinedDictionary(aruco::DICT_4X4_50);
Ptr<aruco::DetectorParameters> parameters = aruco::DetectorParameters::create();

//    Wzytanie obrazu zawierającego ArUco
Mat image = imread("aruco.png");
Mat gray;
cvtColor(image, gray, COLOR_BGR2GRAY);

//    Wykrycie ArUco
vector<int> ids;
vector<vector<Point2f>> corners;
aruco::detectMarkers(gray, dictionary, corners, ids, parameters);

//    Jeśli znaleziono ArUco markery, oblicz odległość między nimi
if (ids.size() >= 2){
//    Pobieramy współrzędne środków
Point2f center1 = (Point_<float> &&) mean(corners[0]).val;
Point2f center2 = (Point_<float> &&) mean(corners[1]).val;

//    Obliczamy odległość między środkami
double distance = norm(center1 - center2);

//    Wyświetlamy wynik
cout << "Odległość między markerami: " << distance << endl;
}

//Jeśli jest tylko jeden lub zero marker/ów to wyświetlamy komunikat
else if (ids.size() == 1){
cout << "Znaleziono jeden marker" << endl;
}
else{
cout << "Nie znaleziono żadnych markerów" << endl;
}
    return 0;
}