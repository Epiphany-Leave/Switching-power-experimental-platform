% 清空所有图形和变量
close all;
clear;
clc;
% 电流环传递函数
numerator_i = [0.00068*0.08 0.00068*0.05+0.08*0.005 0.05*0.005];
denominator_i = [0.00068 0.005+0.08 0.05];
Ti = tf(numerator_i, denominator_i);
% 电压环传递函数
% numerator_v = [1 10];
% denominator_v = [16.5e-6 0.5 5];
% Tv = tf(numerator_v, denominator_v);
% 电流环根轨迹
figure;
rlocus(Ti);
title('电流环传递函数的根轨迹', 'FontSize', 14);
xlabel('实轴', 'FontSize', 12);
ylabel('虚轴', 'FontSize', 12);
grid on;
set(gca, 'FontSize', 12);
% 电压环根轨迹
% figure;
% rlocus(Tv);
% title('电压环传递函数的根轨迹', 'FontSize', 14);
% xlabel('实轴', 'FontSize', 12);
% ylabel('虚轴', 'FontSize', 12);
% grid on;
% set(gca, 'FontSize', 12);
% 电流环频率响应
figure;
bode(Ti);
title('电流环传递函数的频率响应', 'FontSize', 14);
grid on;
set(findall(gcf,'Type','line'),'LineWidth',2);
set(findall(gcf,'-property','FontSize'),'FontSize',12);
% 电压环频率响应
% figure;
% bode(Tv);
% title('电压环传递函数的频率响应', 'FontSize', 14);
% grid on;
% set(findall(gcf,'Type','line'),'LineWidth',2);
% set(findall(gcf,'-property','FontSize'),'FontSize',12);
% 显示所有图形
drawnow;