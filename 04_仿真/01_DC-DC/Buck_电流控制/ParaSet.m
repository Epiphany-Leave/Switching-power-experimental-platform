%% 交错并联 BUCK - 增强型整定工具 (SS版)
clear; clc; close all;

%% 1. 系统硬件参数 (保持你之前的输入)
Vin = 24;           
Vout = 12;          
Iout_max = 6;       
L_phase = 68e-6;     
C_out = 440e-6;     
R_load = Vout/Iout_max; 
Fs = 40000;         
Ts = 1/Fs;

%% 2. 建立数学模型
L_eq = L_phase / 2; 
s = tf('s');
Gid = Vin * (s * C_out * R_load + 1) / (s^2 * L_eq * C_out * R_load + s * L_eq + R_load);

%% 3. PI 控制器整定
Fc_i = Fs / 10;     
wc_i = 2 * pi * Fc_i;
wz_i = wc_i / 5;

[mag, ~] = bode(Gid, wc_i);
mag_at_Fc = squeeze(mag);
Kp_current = 1 / mag_at_Fc; 
Ki_current = Kp_current * wz_i;

C_i = Kp_current + Ki_current / s;
L_i = C_i * Gid;

%% 4. 离散化与时滞处理 (消除警告的关键)
C_z = c2d(C_i, Ts, 'tustin');
% 考虑 1.5Ts 的采样与计算延迟
Delay = exp(-1.5 * Ts * s);
% 将模型转换为状态空间 (State-Space) 以消除 feedback 警告
Gid_delayed_z = c2d(Gid * Delay, Ts, 'zoh');
L_z_delayed = ss(C_z * Gid_delayed_z); 

%% 5. 弹窗 1：伯德图分析
figure('Name', 'Bode Plot - Stability Analysis', 'Color', 'w', 'Position', [100, 100, 800, 600]);
opts = bodeoptions;
opts.FreqUnits = 'Hz';
opts.Grid = 'on';
opts.XLim = [10, Fs*2];
bode(Gid, 'r--', L_i, 'b', L_z_delayed, 'g', opts);
legend('被控对象 (Plant)', '连续域开环 (Loop Gain)', '离散域+延迟 (Discrete Loop)');
title('电流环 Bode 图 (检查相位裕度)');

%% 6. 弹窗 2：阶跃响应分析
figure('Name', 'Step Response - Dynamic Performance', 'Color', 'w', 'Position', [920, 100, 800, 600]);
% 使用状态空间进行闭环计算，避免警告
G_close_continuous = feedback(ss(L_i), 1);
G_close_discrete = feedback(L_z_delayed, 1);
step(G_close_continuous, 'b', G_close_discrete, 'g');
grid on;
legend('连续域闭环', '离散域闭环');
title('电流环闭环阶跃响应 (1A Step)');
ylabel('电流 (A)');

%% 7. 结果输出
[Gm, Pm, ~, Wcp] = margin(L_z_delayed);
fprintf('========================================\n');
fprintf('  电流环整定结果 (针对 F280049C)\n');
fprintf('----------------------------------------\n');
fprintf('Kp: %.6f | Ki: %.6f\n', Kp_current, Ki_current);
fprintf('截止频率 (Fc): %.2f Hz\n', Wcp/(2*pi));
fprintf('相位裕度 (PM): %.2f deg\n', Pm);
fprintf('========================================\n');