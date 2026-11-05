clc; clear; close all;

% 电流范围：0~6A
I = linspace(0, 6, 100);

% DCR范围：0.02Ω~1Ω
R_DCR = linspace(0.02, 1.0, 100);

% 网格
[I_grid, R_grid] = meshgrid(I, R_DCR);

% DCR损耗
P_loss = I_grid.^2 .* R_grid;

% 绘图
figure;
surf(I_grid, R_grid, P_loss);
xlabel('电感电流 I / A');
ylabel('电感DCR / Ω');
zlabel('电感铜损 P_{DCR} / W');
title('电感DCR对损耗的影响');
grid on;
shading interp;
colorbar;