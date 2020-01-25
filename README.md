# Indicator upower for Ubuntu Touch

A upower indicator for Ubuntu Touch, spin-off from bhdouglass's Indicator Weather.
it's uses data from the cli command [Upower ](https://upower.freedesktop.org/) embedded into the Ubuntu touch operating system.

Upower is devices dependent, please raise a bug to enable your devices.

[![OpenStore](https://open-store.io/badges/en_US.png)](https://open-store.io/app/indicator.upower-ernesst)

Known support :
|   Devices  | Status |    Current   | Temperature | Charge | Voltage | Remaining life  | Limit battery's charge |
|:----------:|:------:|:------------:|:-----------:|:------:|:-------:|:---------------:|:----------------------:|
|   OP3(T)   |    x   |       x      |      x      |    x   |    x    |        x        |            x           |
|    Mako    |    x   |       x      |      x      |    x   |    x    |        x        |           no           |
| Hammerhead |    x   |       x      |      x      |    x   |    x    |        no       |           no           |
|   Cedric   |    x   |       x      |      x      |    x   |    x    |        x        |           no           |
|    Bacon   |    x   |       x      |      x      |    x   |    x    |        no       |           no           |
|  vegetahd  |    x   | not reliable |      x      |    x   |    x    |        no       |           no           |

## Installation
- Install the application from OpenStore,
- Go to the upower app, set setting and save,
- install the indicators,
- Reboot.

## Translating

To be enable

## About the Indicator
As for Indicator Weather, the indicator itself is rather simple. It's a python script that exports a Gtk
menu over DBus. To start the script there is an Upstart config file located at
.config/upstart/ernesst-indicator-upower.conf. This starts the indicator when
Unity starts the rest of the indicators. The other important file is
.local/share/unity/indicators/com.ernesst.indicator.upower. This file lets Unity know where to
find the indicator on DBus and where to place the indicator on the indicator bar.

If you are interested in creating your own indicator for Ubuntu Touch and have
questions, I would be glad to help.
Moreover the Indicator Master, Brian Douglass, can be Just contact via [my website](https://bhdouglass.com/contact.html).

## Building

The easiest way to compile and package indicator upower is via [clickable](https://github.com/bhdouglass/clickable).

## Logo

The logo is from the [gusbemacbe github repository of Suru-plus icons](https://github.com/gusbemacbe/suru-plus).

## Donate

Please consider giving a small donation to the [Ubports project](https://ubports.com/donate).

## License

Copyright (C) 2019 Ernesst

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License version 3, as published
by the Free Software Foundation.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranties of MERCHANTABILITY, SATISFACTORY QUALITY, or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>.
