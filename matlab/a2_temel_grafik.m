clc;
clear;
clear all;
x = 0:1:10;
y = x;
plot(x,y) %x ve y eksenleri verilen grafik
grid off %grid ekran seklinde gösterir parametre  olarak "on" ve "off" kullanılır
xlabel("x ekseni") %x eksenine isim veriririz
ylabel("y ekseni") %y eksenine isim veririz
title("Başlık") %grafiğe başlık vermek 
axis([0 5 0 5]) %grafikte gösterilecek aralığı gösteriri ilk iki hane x sonra ki ye