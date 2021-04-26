
#ifndef interval_h
#define interval_h

/* Interval
 * Copyright (C) 2014, 2016  Pavel Brychta http://www.xpablo.cz
 * updated by Radim Keseg in 2021
 * 
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License along with this program. If not, see http://www.gnu.org/licenses 
 */

#include <inttypes.h>

class Interval
{
  protected:
	uint32_t timefrom;
	uint32_t timeout;
  public:
	bool expired(void);
	void set(uint32_t tmout);
	uint32_t getTimeout(void);
	uint32_t elapsed(void);
	uint32_t remains(void);
};

#endif
// EOF

