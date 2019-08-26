# cpuid

CFEngine module for calling CPUID

## Installation

On FreeBSD, NetBSD and OpenBSD

    sudo make install

On Mac OS X you will need to install bsdmake from homebrew

    brew install bsdmake
    sudo bsdmake install

On Ubuntu you will need to install the freebsd-buildutils package along with
bmake

    sudo apt-get install freebsd-buildutils bmake
    sudo bmake install

## Example Usage

    body common control
    {
        bundlesequence => { "identify_cpu" };
    }

    bundle agent identify_cpu
    {
        classes:

            "has_avx_support" expression => strcmp("avx", "$(cpuid.features)");

        commands:

            any::

                "/var/cfengine/modules/cpuid"
                    comment => "Retrieve CPU vendor and processor features",
                    module => "true";

        reports:

            any::

                "$(cpuid.features)";

            intel::

                "this host has an $(cpuid.vendor) processor";

            has_avx_support::

                "this host supports the avx instruction set";
    }

    sudo /var/cfengine/bin/cf-agent -K -f ./cpuid_example.cf
    R: this host has an intel processor
    R: EAX=1 Features:
    R:      fpu
    R:      vme
    R:      de
    R:      pse
    R:      tsc
    R:      msr
    R:      pae
    R:      mce
    R:      cx8
    ... snip ...
    R: this host supports the avx instruction set

[![Build Status](https://travis-ci.org/skreuzer/cpuid.svg?branch=master)](https://travis-ci.org/skreuzer/cpuid)
