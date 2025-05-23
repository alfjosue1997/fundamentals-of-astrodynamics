% ------------------------------------------------------------------------------
%
%                              Ex2_1.m
%
%  this file demonstrates example 2-1.
%
%                          companion code for
%             fundamentals of astrodyanmics and applications
%                                 2022
%                            by david vallado
%
%  author        : david vallado             davallado@gmail.com      20 jan 2025
%
% ------------------------------------------------------------------------------

    constmath;

    % --------  newtonm      - find true and ecc anomaly given ecc and mean anomaly
    ecc = 0.4;
    m = 235.4/rad;
    
    fprintf(1,'               m                e           nu           e0   \n');
    
    [e0, nu]= newtonm(ecc, m);
    
    fprintf(1,'newm  %14.8f %14.8f %14.8f %14.8f  rad \n',m, ecc, nu, e0 );
    fprintf(1,'newm  %14.8f %14.8f %14.8f %14.8f  deg \n',m*rad, ecc, nu*rad, e0*rad );

    
