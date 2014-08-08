WriteSmart
==========

Zabavna edukativna igra namijenjenja učenju. Odgovori na pitanje padaju,
a vaš cilj je da pokupite pravi odgovor. Vaš lik je pod uticajem nepoznatih
sila i sa strelicama morate da ga održite na pravom putu. 

Autor: Darko Lukić, student na Fakultetu tehničkih nauka u Novom Sadu
Mentor: Lazar Stričević, asistent na Fakultetu tehničkih nauka u Novom Sadu

Kompajliranje
-------------

Potrebno je nabaviti sljedeće biblioteke:
	- libsdl1.2-dev
	- libsdl-ttf1.2-dev
	- libsdl-image1.2-dev
	- libsdl-gfx1.2-dev

U Terminalu ući u direktorijum gdje se nalazi aplikacije i komandom **make**
kompajlirati izvorni kod. Za pokretanje igrice možete koristiti komandu 
**./WriteSmart**.

Kontrole
--------

Lijeva i desna strelica – odabir nivoa, pomjeranje lika lijevo, desno,
[Enter] – pokretanje igre, potvrda imena i ponovno pokretanje igre.

Dodavanje/izmjena pitanja
-------------------------

Pitanja je moguće dodati i/ili izmijeniti u datoteci **data/Questions.txt**,
a pitanja su u formatu:

```
pitanje
prvi odgovor
drugi odgovor
treci odgovor
redni broj tačnog odgovora - 1
```

Licenca
-------

Aplikacije je pod GPL v3 licencom, detaljne informacije nalaze se u datoteci 
**licence/gpl.txt**. U direktorijumu licence se nalaze još i licenca font.

Kontakt
-------

EMail: lukicdarkoo@gmail.com
WebSite: spespro.com
