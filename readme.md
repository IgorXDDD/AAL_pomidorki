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


## Kompilacja i uruchomienie
Do kompilacji i uruchamiania projektu użyty był `CMake` a dokładniej wersja wbudowana w środowisko `CLion` firmy JetBrains. 

`CMakeLists.txt` używany jako plik konfiguracyjny `CMake` zawiera w sobie informacje o kompilacji i budowaniu dwóch programów: `AAL_pomidorki`  oraz `AAL_generator`.

## Pliki źródłowe
Projekt składa się z 10 głównych plików:
- algorithm.hpp
- base.hpp
- field.hpp
- generator.hpp
- naive.hpp
- algorithm.cpp
- externalGenerator.cpp
- generator.cpp
- main.cpp
- naive.cpp

### `base.hpp`
Plik zawiera deklaracje klasy bazowej `BaseAlgorithm`, będącej interfejsem dla dwóch algorytmów zdefiniowanych później (główny i właściwy).

### `algorithm.hpp` oraz `algorithm.cpp`
Pliki zawierają definicję klasy opracowanego przez nas algorytmu - `Algorithm`. W stosunku do klasy bazowej `BaseAlgorithm`, nadpisane zostały: konstruktor oraz metoda `run()`, uruchamiająca algorytm. Ponadto zostały dodane metody `run_instance()` oraz `swap_h_w()` wynikające z konieczności dwukrtotnego uruchomienia algorytmu w przypadku gdy zadana płachta przykrywająca krzaki ma różną szerokość oraz wysokość (gdy nie jest kwadratowa).

### `naive.hpp` oraz `naive.cpp`
Pliki zawierają definicje klasy algorytmu naiwnego - `Naive`. W stosunku do klasy bazowej zostały poczynione takie same zmiany oraz dodania jak w przypadku klasy `Algorithm`.

### `field.hpp`
Plik ten zawiera definicję klasy pola `Field`. Pole składa się z informacji o minimalnej współrzędnej, na której mogą znajdować się krzaki (nominalnie 0), maksymalnej współrzędnej, na której mogą znajdować się krzaki (nominalnie 60000, wartość tę można modyfikować). Najważniejszym elementem pola jest wektor krzaków, reprezentowany przez wektor par dwóch liczb nieujemnych, przy czym pierwsza z pary dla danego elementu wektora (dla danego krzaczka pomidorów) reprezentuje współrzędną `x` jaką zajmuje na polu dany krzak a druga liczba z pary rezprezentuje współrzędną `y` owego krzaczka.

### `generator.hpp` oraz `generator.cpp`
Pliki te zawierają definicje generatora, który jest używany do stworzenia instancji problemu. Klasa `Generator` zawiera w sobie informacje o liczbie krzaków, jaką obiekt tej klasy powinien wygenerować oraz informacje o polu w postaci obiektu klasy `Field`. Każdy z krzaków jest losowany niezależnie a ponadto każdorazowe przeglądanie dotychczas wylosowanych współrzędnych sprawia, że niemożliwa jest sytuacja w której dwa krzaczki miały by te same współrzędne. Generowanie pola odbywa się przy pomocy funkcji `rand()` z biblioteki `cstdlib` - problem przekroczenia zakresu przez funkcję `rand()` został rozwiązany w ten sposób, że w przypadku gdy rozmiar pola przekracza `RAND_MAX` (górną granicę liczb zwracanych przez `rand()`) to następuje dolosowanie brakującej części danej współrzędnej. 

Przykładowo, kiedy zadany rozmiar pola n przekracza `RAND_MAX` to najpierw losujemy liczbę z przedziału [0,`RAND_MAX`) a następnie powiększamy ją o losową liczbę z przedziału [0,`n`-`RAND_MAX`).

### `externalGenerator.cpp `
W ramach projektu zaimplementowany został generator danych wejściowych do programu (jako oddzielny program). Jego implementacja znadjuje się w pliku `Projekt/src/externalGenerator.cpp`. Argumentami wejściowymi generatora są informacje o generowanym polu oraz informacje o płachcie, są potrzebne obie te rzeczy ponieważ zadaniem generatora jest przygotwać takie dane, które będą stanowiły pełną instancję problemu.
Przykładowe użycie generatora:
```
AAL_generator.exe -n30000 -k2000 -h300 -w500 > dane.txt
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

### `main.cpp`
Plik, zawierający funkcję `main()`, z której to uruchamiany jest algorytm. W tym pliku zostało zaimplementowane parsowanie argumentów wejściowych, użyta do tego została bilbioteka `regex`. Oprócz samego parsowania w pliku znajduje się także zaimplementowane działanie wszystkich trybów uruchomienia, opisane zostały one poniżej.

## Tryby uruchomienia
Program przewiduje 4 tryby uruchomienia:
1. Z flagą `-m1` - tryb ten przyjmuje informacje o danych wejściowych ze standardowego wejścia i wypisuje wynik na standardowe wyjście. Tryb ten powinien mieć podane dane wygenerowane przez generator (plik generator.cpp).
   Przykładowe (zalecane) użycie programu w trybie pierwszym:
   ```
   AAL_generator.exe -n5000 -k1000 -h200 -w400 | AAL_pomidorki.exe -m1
   ```
2. Z flagą `-m2` - tryb generowania i rozwiązania problemu, jako argumenty podawane są dodatkowo flagi: 
   1. `-k`  - określa liczbę wygenerowanych krzaków
   2. `-h` - określa wysokość płachty
   3. `-w` - określa szerokość płachty
   4. `-n` - parametr opcjonalny, określa rozmiar pola (długość krawędzi)
   
   Przykładowe użycie:

   ```
   AAL_pomidorki.exe -m2 -k4000 -h300 -w200
   ```
   powyższe uruchomienie oznacza dokładnie: wygeneruj instancję problemu dla domyślnej wielkości pola równej = `60000x60000` oraz 4000 krzaków pomidorów. Następnie rozwiąż ten problem przy użyciu płachty o wymiarach `300x200`
3. Z flagą `-m3` - tryb "benchmarkowy", jako argumenty przyjmuje informacje o generowanym polu oraz płachcie (dokładnie tak samo jak w trybie `-m2`) i jeszcze przyjmuje dodatkowo informacje o przyroście wielkości problemu, liczbie wykonań algorytmu dla problemu o zadanej wielkości oraz liczbie przyrostów. 

   Używane flagi:
      1. `-step` - określa jak duży ma być przyrost wielkości problemu
      2. `-r` - określa ile razy ma nastąpić zwiększenie wielkości problemu
      3. `-c` - określa ile razy dla zadanej wielkości problemu ma być wywołany algorytm
      4. `-hwi` - flaga opcjonalna, określa czy wymiary płachty mają się zwiększać dla każdej kolejnej wielkości problemu
      
   Pozostałe flagi: `-n`,`-k`,`-h`,`-w` mają dokładnie to samo znaczenie co w trybie `-m2`
   
   Przykładowe użycie:
   ```
   AAL_pomidorki.exe -m3 -n10000 -k1000 -h300 -w200 -step100 -r5 -c10
   ```
   Powyższe uruchomienie oznacza dokładnie: 
   - Rozwiąż 10 razy problem o wielkościach: n=10000, k=`1000`, h=300, w=200
   - Rozwiąż 10 razy problem o wielkościach: n=10000, k=`1100`, h=300, w=200
   
   -  ...
   - Rozwiąż 10 razy problem o wielkościach: n=10000, k=`1500`, h=300, w=200
  
   W przypadku dołączenia flagi `-hwi` wraz z wartością `k` zwiększały by się wartości `h` oraz `w` o wartość zadaną w `-step`, w tym przypadku również o 100.

   Dla każdego z 10 uruchomień problem jest generowany na nowo, tzn za (prawie) każdym razem algorytm dostaje inne pole na wejściu.

   Dla każdej wielkości problemu (każdego zestawu danych) jest zapamiętywany średni czas działania algorytmu, który na koniec działania jest wypisywany w kolumnie tabelki, wraz ze znormalizowanym rozmiarem problemu oraz wartością funkcji `q()` zależną od czasu wykonania dla najbardziej środkowej wielkości problemu (mediany).
   Poprzez normalizację problemu rozumiemy podzielenie wszystkich czynników, składających się na rzeczywisty rozmiar, przez 100. Bez owej normalizacji współczynnik `c`, który również jest wypisywany przy zakończeniu obliczeń, byłby tak mały, że program by go zapisywał przy użyciu notacji wykładniczej. Wielkość, jaka jest oznaczona jako `size` to: $k/100*k/100*max(h,w)/100$.

   Przykładowy wynik działania programu w trybie `-m3`:
   ```
   AAL_pomidorki.exe -m3 -n3000 -k100 -h50 -w60 -step10 -r10 -c10 -hwi
   
      WSPOLCZYNNIK c = 57.0724
      size = k*k*max(h,w)/1000000
      
      size    t(size)[ms]     q(size)
      0.6     30.7255 0.897266
      0.847   44.7386 0.925492
      1.152   62.7548 0.954483
      1.521   83.4579 0.961417
      1.96    108.797 0.972598
      2.475   141.254 1
      3.072   181.872 1.03733
      3.757   221.611 1.03353
      4.536   268.22  1.03607
      5.415   320.131 1.03586
   ```
   Kolumny w tabelce są oddzielone tabulacjami, nie jest to wygodne do przeglądania wyników w terminalu, dlatego warto przekierować wynik działania programu do osobnego pliku tekstowego a nastepnie ten wczytać w programie do przetwarzania danych np. `Microsoft Excel`.

4. Z flagą `-m4` - tryb porównawczy z algorytmem naiwnym. Przyjmowane są argumenty identyczne co w trybie nr 2 (`-m2`). Uruchamiane są dwa algorytmy: nasz algorytm oraz algorytm naiwny, mający złożoność $n^2*k$. Uruchamiając ten tryb zaleca się użyć flagi `-n` z wartością nie przekraczającą 2000. Dla wartości `-n1000` algorytm naiwny wykonywał obliczenia ponad 3 razy dłużej niż algorytm główny (ponad 100 sekund na komputerze z procesorem o taktowaniu 3.8 GHz).

   Przykładowe użycie:
      ```
      AAL_pomidorki.exe -m4 -n1000 -k400 -h300 -w200
      ```

Wynik działania programu dla uruchominia w trybie `-m4`:
```
      AAL_pomidorki.exe -m4 -n500 -k1000 -h90 -w80

        Nasz algorytm znalazl w: 1.16338 sekund
        najlepszy wynik:
        52 krzakow przykrytych dla punktu: (269, 89)
        Wymiary plachty: 80 x 90

        Naiwny algorytm znalazl w: 7.87345 sekund
        najlepszy naiwny wynik:
        52 krzakow przykrytych dla punktu: (269, 89)
        Wymiary plachty: 80 x 90
```
Wypisywanie są informacje o czasie działania obu algorytmów oraz informacje o wyniku, jaki dany algorytm wyprodukował. W skład wspomnianego wyniku wchodzą:
- maksymalna liczba krzaków pomidorków, jaka może zostać przykryta przez płachtę o zadanych wymiarach
- punkt zaczepienia płachty, a dokładniej informacja w którym punkcie powinien zostać umieszczony lewy górny wierzchołek płachty
- wymiary płachty - jest to informacja mówiąca jaka jest orientacja płachty (czy płachta jest umieszczona poziomo czy może pionowo). Oczywiście pierwsza z liczb oznacza rozciągnięcie płachty wzdłuż osi `x` a druga z liczb oznacza rozciągnięcie wzdłuż osi `y`. Dla płachty kwadratowej informacja o orientacji nie będzie miała znaczenia.
  
Tryby uruchomienia `-m1` oraz `-m2` wypisują wynik w dokładnie taki sam sposób co tryb `-m4` (bez informacji o algorytmie naiwnym).