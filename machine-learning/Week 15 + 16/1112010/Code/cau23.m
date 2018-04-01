%Truong Minh Anh - 1112010
%truongminhanh93.it@gmail.com
%----------------------------

function [err_in min_err_in max_err_in P] = cau23(features_in)
    %khoi tao cac bien
    ones_mat = ones(1, length(features_in));
    err_in = ones(1, 10);

    %khoi tao nhan training set
    in_label = ones(length(features_in), 10);
    for i = 1:10
        tmp_index = i - 1;
        in_label(:, i) = (features_in(:, 1) == tmp_index);
    end

    %khoi tao nhan test set
    out_label = ones(length(features_in), 10);
    for i = 1:10
        tmp_index = i - 1;
        out_label(:, i) = (features_in(:, 1) == tmp_index);
    end

    for i = 1:10
        %huan luyen va cho ra ket qua
        model = svmtrain(in_label(:, i), features_in(:, 2:3), '-t 1 -c 0.01 -d 2 -q');
        [predicted_label] = svmpredict(out_label(:, i), features_in(:, 2:3), model, '-q');
        P = model;

        %tinh do loi
        err_label = out_label(:, i) ~= predicted_label(:);
        err_in(i) = ones_mat * err_label;
        err_in(i) = err_in(i) / length(features_in);
    end
    
    %tinh vi tri min-max do loi
    [tmp min_err_in] = min(err_in);
    [tmp max_err_in] = max(err_in);
    min_err_in = min_err_in - 1;
    max_err_in = max_err_in - 1;
end