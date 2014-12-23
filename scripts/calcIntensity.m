## Copyright (C) 2014 David Wright
## 
## This program is free software; you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 3 of the License, or
## (at your option) any later version.
## 
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
## 
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <http://www.gnu.org/licenses/>.
## Author: David Wright <wright@indel.ch>
## Created: 2014-12-23


windowSize = 9;
ampl = 0xEF;
numLeds = 32;

intensity = zeros(1, numLeds+3*windowSize);

for i = 1:(windowSize+1)/2
    intensity(i) = ampl/((windowSize+1)/2) * (i-1);
end;
for i = (windowSize+1)/2 : windowSize
    intensity(i) = ampl - ampl/((windowSize+1)/2) * (i -(windowSize+1)/2) ;
end;
plot(intensity);
