Feel free to tranlate in your language

<h1>Translation DE</h1>
<h2>Kamera</h2>
<h3>AT+CAMSTART</h3>
Startet die Kamera
AT+CAMSTART=0,QVGA Format
AT+CAMSTART=1， VGA Format
AT+CAMSTART=2， QQVGA Format
<h3>AT+CAMSTOP</h3>
Stopt die Kamera
<h3>AT+CAMCAP</h3>
Bild aufnehmen.
<h3>AT+CAMRD</h3>
Liest die Kamera aus
AT+CAMRD=fromaddr,toaddr;
AT+CAMRD=0 //Start bei 0 bis ende
AT+CAMRD=5,10 //zwischen adresse 5 und 10 
<h3>AT+CAMREC</h3>
Noch nicht unterstützt
<h3>AT+CAMPOST</h3>
Foto-Inhalte können über diese Anweisung über ein Standard-POST-Protokoll an den HTTP-Server hochgeladen werden;
AT+CAMPOST=<”HTTP-Server Adresse”>,<port>
Return:
+CAMPOST:1 erfolgreich gesendet
+CAMPOST:0 fehler
Beispiel:
AT+CAMPOST=”192.168.1.111/A6C/123.jpg”,80 //Fotos an die Adresse des Content-Server senden
<h3>AT+CAMCFG</h3>
Konfigurieren Sie die Kamera.
Befehlsformat ist wie folgt:
AT+CAMCFG=mode,param

mode|Beschreibung|Parameter
--- | --- | ---
0|Blitz|0 geschlossen 1 automatisch 2 offen
1|Nachtsicht|0 aus 1 ein
2|Bildqualität|0  1  2 ?
3|Rotation|0 keine 1 90 Grad 2 180 Grad 3 270 Grad
4|Belichtung|-2,-1,0,1,2
5|Helligkeit|-2,-1,0,1,2
6|Weißabgleich|0-auto,1-Tageslicht,2-Kunstlicht(0x08),3-Bewölkt(0x09),4-Glühbirne(0x0a)
7|Kontrast|1-5
