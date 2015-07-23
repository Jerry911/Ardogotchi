/*
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# authors: Jeroen Pleysier (jeroen.pleysier@gmail.com)
# date: 2014-10-10
# version 1.1
# description: Simple counter
*/

#ifndef Couter_h
#define Counter_h

class Counter{
  public:
    void increment(int ammount);
    void decremet(int ammount);
    int getAmmount();
    void reset();
};

#endif
