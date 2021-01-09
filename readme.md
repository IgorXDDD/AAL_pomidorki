# Readme
## Autorzy:
1. Igor Kaźmierczak 293118
2. Bartłomiej Olber 300237

## Treść zadania
Rolnik musi zabezpieczyc swoja plantacje pomidorków przed inwazja stonki pomidorozernej
poprzez przykrycie krzaków pomidorków płachta przezroczystego plastiku. Niestety -
plantacja jest wieksza niz posiadana przez rolnika płachta, zatem musi on wybrac takie jej
połozenie, w którym mozliwie duza liczba krzaków bedzie przykryta. Plantacja ma postac
kwadratu o bokach 60000 na 60000 metrów. Rolnik dysponuje płachta o wymiarach a × b,
gdzie a, b < 10000. Na plantacji rosnie k < 15000 krzaków pomidorków o znanych rolnikowi
współrzednych. Zaproponuj algorytm, który musi dla ustalonego zbioru współrzednych
krzaków pomidorków zaproponuje optymalne połozenie płachty plastiku (przy czym
przyjmujemy, iz krzak znajdujacy sie na brzegu płachty jest takze przez nia przykryty).

## Pliki źródłowe
Projekt składa się z 4 głównych plików:
- algorithm.hpp
- generator.hpp
- generator.cpp
- main.cpp

### algorithm.hpp
Plik ten zawiera deklarację oraz definicję klasy algorytmu. Obiekt owej klasy zawiera w sobie informacje o rozmiarach instancji problemu 

### generator.cpp 
W ramach projektu zaimplementowany został generator danych wejściowych do programu (jako oddzielny program). Jego implementacja znadjuje się w pliku `Projekt/generator.cpp`. Generator ten powinien zostać skompilowany przy użyciu kompilatora obsługującego co najmniej C++11 (biblioteka regex). Argumentami wejściowymi generatora są informacje o generowanym polu oraz informacje o płachcie, są potrzebne obie te rzeczy ponieważ zadaniem generatora jest przygotwać takie dane, które będą stanowiły pełną instancję problemu.
Przykładowe użycie generatora:
```
generator.exe -n30000 -k2000 -h300 -w500 > dane.txt
```
Takie uruchomienie generatora zapisze do pliku dane.txt dane problemu o następujących wartościach:
- rozmiar krawędzi pola (n) = 30000 m 
- liczba krzaków pomidorków umieszczona na polu (k) = 2000
- długość/wysokość płachty (h) = 300
- szerokość płachty (w) = 500

Format danych, znajdujących się w pliku wyjściowym prezentuje się następująco: 
```
h w
n k
wsp_1_1 wsp_1_2
wsp_2_1 wsp_2_2
...
wsp_k_1 wsp_k_2
```
Na początku znajdują się informacje o płachcie (długość i szerokość), następnie są informacje o polu (rozmiar i liczba krzaków) całą resztę pliku stanowią informacje o położeniu poszczególnych krzaków: `wsp_i_1`, `wsp_i_2` oznacza kolejno: współrzędną `x` oraz współrzędną `y` i-tego punktu.

Uruchomienie generatora bez podania flagi `-n` sprawi że wygeneruje on dane dla pola o wymiarach domyślnych dla problemu (n=60000).


## Tryby uruchomienia
Program przewiduje 3 tryby uruchomienia:
1. Z flagą `-m1` - tryb ten przyjmuje informacje o danych wejściowych ze standardowego wejścia i wypisuje wynik na standardowe wyjście. Tryb ten powinien mieć podane dane wygenerowane przez generator (plik generator.cpp).
   Przykładowe (zalecane) użycie programu w trybie pierwszym:
   ```
   generator.exe -n5000 -k1000 -h200 -w400 | program.exe -m1
   ```
2. Z flagą `-m2` - tryb generowania i rozwiązania problemu, jako argumenty podawane są dodatkowo flagi: 
   1. `-k`  - określa liczbę wygenerowanych krzaków
   2. `-h` - określa wysokość płachty
   3. `-w` - określa szerokość płachty
   4. `-n` - parametr opcjonalny, określa rozmiar pola (długość krawędzi)
   
   Przykładowe użycie:
   ```
   program.exe -m2 -k4000 -h300 -w200
   ```
   powyższe uruchomienie oznacza dokładnie: wygeneruj instancję problemu dla domyślnej wielkości pola równej = `60000x60000` oraz 4000 krzaków pomidorów. Następnie rozwiąż ten problem przy użyciu płachty o wymiarach `300x200`
3. Z flagą `-m3` - tryb "benchmarkowy", jako argumenty przyjmuje informacje o generowanym polu oraz płachcie (dokładnie tak samo jak w trybie `-m2`) i jeszcze przyjmuje dodatkowo informacje o przyroście wielkości problemu, liczbie wykonań algorytmu dla problemu o zadanej wielkości oraz liczbie przyrostów. 

   Używane flagi:
      1. `-step` - określa jak duży ma być przyrost wielkości problemu
      2. `-r` - określa ile razy ma nastąpić zwiększenie wielkości problemu
      3. `-c` - określa ile razy dla zadanej wielkości problemu ma być wywołany algorytm
      
   Pozostałe flagi: `-n`,`-k`,`-h`,`-w` mają dokładnie to samo znaczenie co w trybie `-m2`
   
   Przykładowe użycie:
   ```
   program.exe -m3 -n10000 -k1000 -h300 -w200 -step100 -r5 -c10
   ```
   Powyższe uruchomienie oznacza dokładnie: 
   - Rozwiąż 10 razy problem o wielkościach: n=10000, k=`1000`, h=300, w=200
   - Rozwiąż 10 razy problem o wielkościach: n=10000, k=`1100`, h=300, w=200
   
   -  ...
   - Rozwiąż 10 razy problem o wielkościach: n=10000, k=`1500`, h=300, w=200
  
   Dla każdego z 10 uruchomień problem jest generowany na nowo, tzn za (prawie) każdym razem algorytm dostaje inne pole na wejściu.

   Dla każdej wielkości problemu (każdego zestawu danych) jest zapamiętywany średni czas działania algorytmu

