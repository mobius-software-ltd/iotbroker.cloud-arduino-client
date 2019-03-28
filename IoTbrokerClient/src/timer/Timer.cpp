/**
 * Mobius Software LTD
 * Copyright 2015-2018, Mobius Software LTD
 *
 * This is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this software; if not, write to the Free
 * Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA, or see the FSF site: http://www.fsf.org.
 */
 
#include "Timer.h"

Timer::Timer(const Timeout &timeout)
    : _timeout(timeout)
{
}

Timer::Timer(const Timer::Timeout &timeout,
             const Timer::Interval &interval,
             bool singleShot)
    : _isSingleShot(singleShot),
      _interval(interval),
      _timeout(timeout)
{
}

void Timer::start(bool multiThread)
{
    if (this->running() == true)
        return;

    _running = true;

    if (multiThread == true) {
        _thread = std::thread(
                    &Timer::_temporize, this);
    }
    else{
        this->_temporize();
    }
}

void Timer::stop()
{
    _running = false;
    _thread.join();
}

bool Timer::running() const
{
    return _running;
}

void Timer::setSingleShot(bool singleShot)
{
    if (this->running() == true)
       return;

    _isSingleShot = singleShot;
}

bool Timer::isSingleShot() const
{
    return _isSingleShot;
}

void Timer::setInterval(const Timer::Interval &interval)
{
    if (this->running() == true)
       return;

    _interval = interval;
}

const Timer::Interval &Timer::interval() const
{
    return _interval;
}

void Timer::setTimeout(const Timeout &timeout)
{
    if (this->running() == true)
       return;

    _timeout = timeout;
}

const Timer::Timeout &Timer::timeout() const
{
    return _timeout;
}

void Timer::_temporize()
{
    if (_isSingleShot == true) {
        this->_sleepThenTimeout();
    }
    else {
        while (this->running() == true) {
            this->_sleepThenTimeout();
        }
    }
}

void Timer::_sleepThenTimeout()
{
    std::this_thread::sleep_for(_interval);

    if (this->running() == true)
        this->timeout()();
}
