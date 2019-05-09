# Image_Procc

* Wczytuje zadany obraz, umożliwia przetwarzania wg tabelki, a następnie wyniki
przekształceń zapisuje do plików.
* Korzystanie z gotowych bibliotek możliwe dla: odczytania, alokacji, wyświetlania i zapisu obrazu.
* Dozwolone jest korzystanie z gotowej implementacji FFT w wersji 1D.

<b>Przekształcenia punktowe/geometryczne (RGB + mono):</b> 
* Wyrównanie histogramu do rozkładu Gaussa o zadanym odchyleniu.

***

<b>Filtracja przestrzenna (RGB + mono): </b> 
* Ordfilt2 dla zadanego rozmiaru maski i zadanego numeru początkowego.
* (Dla RGB każda warstwa osobno)

___

<b>Przekształcenia morfologiczne (mono + logiczne): </b>
* Zamknięcie elementem linijnym o zadanej długości i nachyleniu.

___

<b>Przekształcenia logiczne: </b>
* Mapa odległości geodezyjnej od zadanego punktu wewnątrz obiektu.

___
