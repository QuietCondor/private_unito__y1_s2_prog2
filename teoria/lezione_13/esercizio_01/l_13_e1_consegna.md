# Consegna
Scrivere un programma in C che gestisca un canile.

## Fasi dell'applicazione
- All'apertura:
  1. Deve essere letto il contenuto di un file
    contenente i cani
  2. Il contenuto dovrà andare in un MULTI-SET contenente i cani
- Durante l'apertura:
  - Si potrà aggiungere un cane
  - Si potrà togliere il cane
  - Visualizzare tutti i cani
  - Uscire
- Alla chiusura:
  - Il contenuto del MULTI-SET dovrà sovrascrivere il contenuto
    attuale del file.

### Ulteriori costrizioni:
- Il MULTI-SET dei cani DEVE essere una lista

## Struttura del file per i cani
- nome cane: Il nome del cane
- razza: La razza del cane come testo libero
- eta: L'età del cane
- genere: Il genere del cane

Esempio:
| nome  | razza    | eta | genere |
|-------|----------|-----|--------|
| Diana | Bassotto | 3   | F      |

## Punti bonus
- Gestire le razze dei canili come SET