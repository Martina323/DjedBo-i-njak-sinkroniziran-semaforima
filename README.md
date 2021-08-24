# DjedBozicnjak-sinkroniziran-semaforima i Filozofi monitorom
Tematika kolegija Operacijski sustavi na Fakultetu elektrotehnike i računarstva u Zagrebu.

DJED BOZICNJAK:
Djed Božićnjak spava u svojoj kući na Sjevernom polu i može biti probuđen ako mu se vrati svih 10 sobova sa njihovog odmora (preciznije posljednji budi Djeda Božićnjaka). 
On ih tada nahrani i ponovo odlazi spavati, a sobovi ostaju pred kućom. Djedovo buđenje mogu izazvati i patuljci koji imaju poteškoća prilikom izrade igračaka.
Ako samo jedan patuljak ima problem, to nije toliko ozbiljno da bi probudio Djeda Božićnjaka, pa zato patuljci posjećuju Djeda Božićnjaka u grupama po 3.
Patuljci kod Djeda Božićnjaka provedu određeno vrijeme te se nakon toga vrate pravljenju igračaka, a Djed Božićnjak spavanju. Samo jedna grupa patuljaka može
 u isto vrijeme ići Djedu Božićnjaku, dok ostali moraju čekati da se ta grupa ne vrati. Ako se Djed Božićnjak probudi i ispred vrata vidi grupu patuljaka (može i manje od tri)
 i sve sobove, on će smatrati da je došlo vrijeme za razvoženje poklona te da patuljci mogu čekati dok ne obavi zadatak. Nakon razvoženja poklona dat će svojim sobovima
 godišnji odmor.  Napišite program koji simulira gornje radnje pazeći na specifičnosti svakog od likova. Ispis programa mora biti detaljan.
 Za svakog "aktera" predvidjeti po jednu dretvu/proces.Ć
 
 FILOZOFI
 S pomoću više dretvi riješiti problem pet filozofa koristeći koncept monitora. Pri svakoj promjeni program mora vizualno prikazati za sve filozofe što oni rade.
 Npr. kada filozof 4 ide jesti, tada treba ispis izgledati otprilike ovako: "Stanje filozofa: X o O X o" (X-jede, O-razmišlja, o-čeka na vilice).
Problem pet filozofa. Filozofi obavljaju samo dvije različite aktivnosti: misle ili jedu. To rade na poseban način. Na jednom okruglom stolu nalazi se pet tanjura te
pet štapića (između svaka dva tanjura po jedan). Filozof prilazi stolu, uzima lijevi štapić, pa desni te jede. Zatim vraća štapiće na stol i odlazi misliti.
Ako rad filozofa predstavimo jednim zadatkom onda se on može opisati na sljedeći način:

filozof i
    ponavljati
        misliti;
        jesti;
    do zauvijek;
