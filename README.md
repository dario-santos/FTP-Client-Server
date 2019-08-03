<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
[![Stars][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![GNU GPLv3 License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]



<!-- PROJECT LOGO -->
<br />
<p align="center">
  <h3 align="center">A FTP Client and Server</h3>

  <p align="center">
    A FTP Client and Server written in C. This is the final project of one of my university subjects.
    <br />
    ·
    <a href="https://github.com/dario-santos/FTP-Client-Server/issues">Report a Bug</a>
    ·
    <a href="https://github.com/dario-santos/FTP-Client-Server/issues">Request a Feature</a>
  </p>
</p>



<!-- TABLE OF CONTENTS -->
## Table of Contents

* [About the Project](#about-the-project)
  * [Built With](#built-with)
* [Getting Started](#getting-started)
  * [Prerequisites](#prerequisites)
  * [Installation](#installation)
* [Usage](#usage)
* [Roadmap](#roadmap)
* [License](#license)
* [Contact](#contact)
* [Acknowledgements](#acknowledgements)



<!-- ABOUT THE PROJECT -->
## About The Project

This project is one of my school projects. It's a FTP client and server that supports file and messages transfer. It was written in ANSI C with posix threads and a syncronization system with locks to allow multiple Clients to send and receive messages, and files, from the server at the same time.

The communication between the Client and the Server is made using name pipes (FIFOS), and as stated before, the server is multithreaded, this way it can handle multiple clients at the same time.

### Built With

* [ANSI C](https://www.pdf-archive.com/2014/10/02/ansi-iso-9899-1990-1/ansi-iso-9899-1990-1.pdf)
* [POSIX](https://en.wikipedia.org/wiki/POSIX)


<!-- GETTING STARTED -->
## Getting Started

### Prerequisites

You will need a C compiler and a UNIX OS

### Installation

1. Clone the repo
```sh
git clone https:://github.com/dario-santos/FTP-Client-Server.git
```
2. Run the Make files inside the Client and the Server folder
a)
```sh
cd Project/Server

make

```
b)
```sh
cd Project/Client

make
```


<!-- USAGE EXAMPLES -->
## Usage

1. Open a terminal and run the server file.
2. Open another terminal and run the client file.
3. Follow the menu to perform the desired functionality.

**Do not kill the Server terminal, if you want to end the Server process terminate all of the Clients and then press q to end it.
If you kill the Server by accident you will need to go to the tmp directory and delete all of the FIFOS there.**


<!-- ROADMAP -->
## Roadmap

See the [open issues](https://github.com/dario-santos/FTP-Client-Server/issues) for a list of proposed features (and known issues).

<!-- LICENSE -->
## License

Distributed under the GNU GPLv3 License. See `LICENSE` for more information.



<!-- CONTACT -->
## Contact

Dário Santos - [LinkedIn](https://www.linkedin.com/in/dariovfsantos) - dariovfsantos@gmail.com

Project Link: [https://github.com/dario-santos/FTP-Client-Server](https://github.com/dario-santos/FTP-Client-Server)



<!-- ACKNOWLEDGEMENTS -->
## Acknowledgements
* [Img Shields](https://shields.io)
* [Choose an Open Source License](https://choosealicense.com)


<!-- MARKDOWN LINKS & IMAGES -->
[stars-shield]: https://img.shields.io/github/stars/dario-santos/FTP-Client-Server
[stars-url]: https://github.com/dario-santos/FTP-Client-Server/stargazers
[issues-shield]: https://img.shields.io/github/issues/dario-santos/FTP-Client-Server
[issues-url]: https://github.com/dario-santos/FTP-Client-Server/issues
[license-shield]: https://img.shields.io/github/license/dario-santos/FTP-Client-Server
[license-url]: https://github.com/dario-santos/FTP-Client-Server/blob/master/LICENSE
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=flat-square&logo=linkedin&colorB=555
[linkedin-url]: https://www.linkedin.com/in/dariovfsantos/

