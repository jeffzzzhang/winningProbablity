// event driven programming, reference codes from MATLAB codes of the thesis, 2016.09.19
//function execute_eventwithoutpast
//global tmpindex src_id dir_src event_list  time
//n = size(event_list, 1); %[n, d] = size(event_list); updated on 16th Feb 2012
//time = event_list{ n,1 };
//command = event_list{ n,2 };
//tmpindex = event_list{ n,3 };
//src_id = event_list{ n,4 };
//dir_src = event_list{ n,5 };
//%eval(command);
//feval(str2func(command));
//event_list(length(event_list(:, 1)), :) = [];