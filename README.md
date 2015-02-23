# cpuid

CFEngine module for calling CPUID

## Installation

    sudo make install

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
    R: this is an intel processor
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
