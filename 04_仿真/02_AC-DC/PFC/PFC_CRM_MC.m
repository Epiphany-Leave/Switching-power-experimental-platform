%% PFC CRM 磁性元件综合设计工具 (整合版)
% 针对铁氧体 PC40 材质, EE 型磁芯
% 包含：电感经验公式计算 + 磁芯/气隙设计 + 三维趋势分析
clear; clc; close all;

%% ================= 1. 全局参数设置 (在此修改) =================

% --- 系统指标 ---
Vi_rated = 220;      % [V] 额定输入电压(用于计算最佳L)
Vo       = 380;      % [V] 输出直流母线电压
P_total  = 4000;     % [W] 总最大输出功率
fmin     = 33000;    % [Hz] 最低开关频率 (建议33kHz)
Eff      = 0.95;     % [-] 预估效率 (用于计算电流)

% --- 架构设置 ---
is_interleaved = true;  % 是否交错? (true=交错双路, false=单路)

% --- 磁性设计参数 (PC40) ---
% 极其重要：设计抗饱和必须用最低输入电压，而非额定电压
Vi_min_design = 176;    % [V] 抗饱和设计的最低电压 (宽范围请设85或90)
B_max_design  = 0.30;   % [T] 设计最大磁通密度 (PC40 100℃饱和约0.39T，留余量)
k_formula     = 1.4;    % [-] 经验公式系数 (对应 sqrt(2))

% --- 绘图开关 ---
show_3d_plot  = true;   % 是否显示三维规划图? (true/false)


%% ================= 2. 最佳电感量计算 =================

fprintf('============================================================\n');
fprintf('             PFC CRM 电感计算与磁芯选型报告\n');
fprintf('============================================================\n');

% 1. 确定单路功率
if is_interleaved
    P_phase = P_total / 2;
    fprintf('模式: 交错并联 (Interleaved)\n');
    fprintf('总功率: %d W | 单路功率: %d W\n', P_total, P_phase);
else
    P_phase = P_total;
    fprintf('模式: 单路 (Single Phase)\n');
    fprintf('计算功率: %d W\n', P_phase);
end

% 2. 执行经验公式
% 公式: L = (Vi^2 - 1.4 * Vi^3 / Vo) / (2 * fmin * P)
Numerator = Vi_rated^2 - k_formula * (Vi_rated^3 / Vo);
Denominator = 2 * fmin * P_phase;

L_val = Numerator / Denominator; % 单位 Henry
L_uH  = L_val * 1e6;             % 单位 uH

fprintf('------------------------------------------------------------\n');
fprintf('【第一步：电感量计算】 (基于 Vi=%d V)\n', Vi_rated);
fprintf('  最佳电感量 L = %.2f uH\n', L_uH);
fprintf('------------------------------------------------------------\n');


%% ================= 3. 磁芯、匝数与气隙设计 =================

% 1. 计算峰值电流 (最恶劣工况)
% I_line_rms_max = P / (Vi_min * Eff)
% I_pk_switch (CRM模式) = 2 * I_line_peak = 2 * sqrt(2) * I_line_rms
I_line_rms_max = P_phase / (Vi_min_design * Eff);
I_pk_switch    = 2 * sqrt(2) * I_line_rms_max;

fprintf('【第二步：物理设计】 (基于 PC40, Vi_min=%d V)\n', Vi_min_design);
fprintf('  设计峰值电流 Ipk : %.2f A (饱和校核点)\n', I_pk_switch);
fprintf('  设计 Bmax        : %.2f T\n', B_max_design);
fprintf('\n  >>> 常用 EE 磁芯计算结果列表:\n');

% 2. 定义磁芯数据库 (型号, Ae有效截面积mm^2)
% 可按需添加更多磁芯
Core_DB = {
    'EE42/21/20', 240;
    'EE55/28/21', 354;
    'EE65/32/27', 535;
    'EE70/33/32', 683;  % 举例
    'EE85/43/35', 830;
};

fprintf('  %-12s | %-6s | %-6s | %-8s | %-12s\n', '磁芯型号', 'Ae', '匝数N', '气隙lg', '评价');
fprintf('  -------------+--------+--------+----------+--------------\n');

mu0 = 4 * pi * 1e-7;

for i = 1:size(Core_DB, 1)
    Core_Name = Core_DB{i, 1};
    Ae_mm2    = Core_DB{i, 2};
    Ae_m2     = Ae_mm2 * 1e-6;
    
    % A. 计算匝数 N >= (L * Ipk) / (Bmax * Ae)
    N_calc = (L_val * I_pk_switch) / (B_max_design * Ae_m2);
    N_real = ceil(N_calc); % 向上取整
    
    % B. 计算气隙 lg = (mu0 * N^2 * Ae) / L
    lg_m  = (mu0 * N_real^2 * Ae_m2) / L_val;
    lg_mm = lg_m * 1000;
    
    % C. 评价逻辑
    if lg_mm > 3.5
        Comment = '气隙过大(损耗高)';
    elseif lg_mm > 2.5
        Comment = '气隙偏大';
    elseif lg_mm < 0.4
        Comment = '气隙过小';
    else
        Comment = '推荐 (Excellent)';
    end
    
    fprintf('  %-12s | %-6d | %-6d | %.2f mm  | %s\n', ...
        Core_Name, Ae_mm2, N_real, lg_mm, Comment);
end
fprintf('  -------------+--------+--------+----------+--------------\n');
fprintf('  *注: 实际磨气隙时需考虑边缘效应，物理深度通常需增加约 10%%-15%%\n');


%% ================= 4. 三维可视化趋势图 =================

if show_3d_plot
    % 定义扫描范围
    v_scan = linspace(176, 264, 40);      % 输入电压范围
    p_scan = linspace(P_total*0.5, P_total*1.5, 40); % 总功率范围
    [V_grid, P_grid_total] = meshgrid(v_scan, p_scan);
    
    % 处理交错功率
    if is_interleaved
        P_grid_calc = P_grid_total / 2;
    else
        P_grid_calc = P_grid_total;
    end
    
    % 矩阵计算公式
    L_matrix_uH = ((V_grid.^2 - k_formula .* (V_grid.^3 ./ Vo)) ./ ...
                  (2 * fmin .* P_grid_calc)) * 1e6;
    
    % 绘图
    figure('Name', 'PFC L Planning', 'Color', 'white', 'NumberTitle', 'off');
    surf(V_grid, P_grid_total, L_matrix_uH);
    
    % 美化
    shading interp;
    colormap jet;
    c = colorbar;
    c.Label.String = 'Inductance L (uH)';
    xlabel('输入电压 Vi (V)');
    ylabel('总输出功率 P (W)');
    zlabel('电感量 L (uH)');
    title(['PFC CRM 电感规划曲面 (Vo=' num2str(Vo) 'V, fmin=' num2str(fmin/1000) 'kHz)']);
    
    % 标记当前设计点
    hold on;
    plot3(Vi_rated, P_total, L_uH, 'ro', 'MarkerSize', 8, 'MarkerFaceColor', 'r');
    text(Vi_rated, P_total, L_uH + 20, ['  当前点: ' num2str(round(L_uH)) 'uH'], ...
         'Color', 'k', 'FontWeight', 'bold', 'BackgroundColor', 'w');
    
    grid on;
    camlight; lighting gouraud; %以此增加立体感
    rotate3d on;
end

fprintf('\n计算完成。\n');