# Monitor zasobów systemowych

![System Monitor Image](gui.png)

## Opis projektu

Nasz projekt to mointor zasobów systemowych, który śledzi i wyświetla różne metryki, takie jak użycie procesora (CPU), użycie pamięci RAM, zajętość przestrzeni dyskowej, liczbę procesów oraz cykle procesora. Aplikacja została zbudowana przy użyciu Qt dla graficznego interfejsu użytkownika oraz QtCharts do wizualizacji danych w czasie rzeczywistym.

## Wątki i sekcje krytyczne

Nasz projekt posiada 6 wątków i 4 mutexy. Każdy wątek odpowiada za monitorowanie jednego zasobu oraz jeden wątek odpowiada za wyświetlanie wyników.
Oto lista naszych wątków:

-cpuThread

-ramThread

-diskSpaceThread

-processThread

-cyclesThread

-displayThread


Dostęp do wspólnych zasobów regulują 4 mutexy. Są to:

-ramMutex

-cpuMutex

-diskSpaceMutex

-staticDataMutex


Pierwsze 3 mutexy odpowiedzialne są za synchronizację dostępu do wykresów (CPU, RAM, zapełnienie dysku C), ostatni za dostęp do klasy przechowującej dane przedstawiane jako liczba (nie wykres), tzn liczbę cykli procesora od uruchomienia oraz liczbę aktywnych procesów. Każdy z wykresów ma własną klasę  której są zaimplementowane metody obsługujące ten wykres. 3 pierwsze mutexy odpowiedzialne za wykresy regulują dostęp do wspólnego zasobu jakim jest kolejka przechowująca dane każdego wykresu, w ostatnim przypadku wspólnym zasobem jest klasa StaticData która posiada 2 zmienne z odczytywanymi wartościami. 
