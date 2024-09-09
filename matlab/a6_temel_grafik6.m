x_label =    "Time [s]";
y_label =    "Position [m]";
main_title = "Position / Time Graph";

t=0:0.1:2*pi;
a=sin(t);
plot(t, a, 'r', LineWidth=2);
grid on;

xlabel(x_label, FontSize=10);
ylabel(y_label, FontSize=10);
title(main_title, FontSize=10);
text(1, 0, "Theta is 90") % grafiğin belirli noktasında yazı yazmayı sağlar
axis([0 6 -1 1])          % grafiğin gösteriliceği aralık
legend("\sigma")