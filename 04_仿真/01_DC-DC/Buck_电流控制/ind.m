clc; clear; close all;

I = 3;   % 单相平均电流，单位A

R_toroid = 0.9;     % 磁环电感DCR，示例
R_molded = 0.05;    % 一体成型电感DCR，示例

P_toroid = I^2 * R_toroid;
P_molded = I^2 * R_molded;

figure;
bar([P_toroid, P_molded]);
set(gca, 'XTickLabel', {'磁环电感', '一体成型电感'});
ylabel('电感铜损 / W');
title('不同类型电感DCR损耗对比');
grid on;