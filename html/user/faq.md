## FAQ/Troubleshooting ##
{:.no_toc}

* TOC
{:toc}

{::options coderay_line_numbers="nil" /}



### What if my computer doesn't meet requirements? ### 
ProjectStreet@Car runs one "app." The [requirements list](join.php#requirements) is for the default app (named *boinc2docker*) and is the only supported App. Older systems are not compatible.

### What is VT-x or AMD-v and why do I need it? ###
{:#vtx}
This is a feature of modern processors (Intel calls theirs "VT-x" and AMD calls theirs "AMD-v") which Virtualbox needs to be able to run 64-bit virtual machines like the ones used by ProjectStreet@Car.

One way to check if your processor supports VT-x/AMD-v is to look up your processor specifications online. It may be easier however to simply try and run ProjectStreet@Car. If you receive any *boinc2docker* jobs it means BOINC has detected that your processor has support. 

However, it may still be that while your processor supports VT-x/AMD-v, these features are turned off in your BIOS. If your *boinc2docker* jobs download but hang for ~5min then die, this may be the case. To enable it, you need to reboot your computer, enter your BIOS, find this option and enable it. Here is an example of what it might look like (although this will vary with BIOS version, it will likely say something about virtualization): 

![test](img/vtx.png)


### I enabled VT-x/AMD-v but jobs say "Scheduler wait: Please upgrade BOINC" ###

If you attempted to run a *boinc2docker* job before enabling VT-x/AMD-v, it is possible your client is stuck in a state where it still thinks this feature is disabled. It will give you a message "Scheduler wait: Please upgrade BOINC to the latest version" and the log files will show "ERROR: Invalid configuration.  VM type requires acceleration but the current configuration cannot support it." To fix this:

* Remove the ProjectStreet@Car project
* Shut down the BOINC client (from Advanced View choose the menu option *Advanced->Shutdown Connected Client*)
* Go to your BOINC folder and edit the file `client_state.xml`
* Remove the line which contains `<p_vm_extensions_disabled>`
* Restart your BOINC client and readd the project

### My computer gets very slow while ProjectStreet@Car is running in the background ###

Some users prefer to have ProjectStreet@Car running at all times in the background, even while they're using their computer. Unfortunately, due to a [regression](https://www.virtualbox.org/ticket/13500) in VirtualBox, on Windows the priority of VirtualBox cannot be set to low, so it may interfere with your usage. As a workaround until VirtualBox is fixed, you can either lower your BOINC global CPU usage, or you can [limit](#limit-cpu) the number of CPUs that Cosmology@Home uses (leaving your other CPUs for native BOINC applications from other projects which *can* be set to low priority). 



### How can I limit the number of CPUs used? ###
{:#limit-cpu}

*boinc2docker* is multi-threaded and will use up all available cores which BOINC allows it to. For example, if in the BOINC computing preferences you have set "Use at most 50% CPU time" and you have a 4-core processor, the job will use two of them. 

If for whatever reason you wish to limit the number of cores used without changing the global BOINC CPU usage, you can do so by creating a file called `"app_config.xml"` in the ProjectStreet@Car project folder and adding the following text, with the "2" under `avg_ncpus` replaced by however many CPUs you want to use (thanks to [Crystal Pellet](http://www.cosmologyathome.org/forum_thread.php?id=7227&nowrap=true#20300)):

~~~xml
<app_config>
    <app>
        <name>boinc2docker</name>
        <max_concurrent>1</max_concurrent>
    </app>
    <app_version>
        <app_name>boinc2docker</app_name>
        <plan_class>vbox64_mt</plan_class>
        <avg_ncpus>2</avg_ncpus>
    </app_version>
</app_config>
~~~

*Notes:* 

* If after this BOINC gives an error reading your `app_config.xml` file, make sure you saved the file with a character encoding apropriate for your system (options to do so may vary by text editor).
* You will need to restart your BOINC client for this take effect
* This will only affect jobs started after you created the file (jobs started before will show "X CPUs" but still run using all of them, you can just abort these) 
* Reseting or removing/readding the project will delete this file so you will have to remake it

### What science is being done with ProjectStreet@Car? ###
{:#science}
Needs to be done. WIP



### How does the *boinc2docker* app work? ###
* These jobs run inside of a [Virtualbox](https://en.wikipedia.org/wiki/VirtualBox) virtual machine. 
* Within the virtual machine, the code itself is packaged within a so called "[Docker](https://www.docker.com/whatisdocker) container". 
* The first thing the jobs do is download the necessary Docker container from the Docker servers. During this download, you will see the job progress frozen at 0.100%. Once the download is complete, the progress bar should continue normally and your CPU usage will jump up as the computation begins. 
* After you run your first *boinc2docker* job, the Docker container which was downloaded will be saved to your computer, so it will not need to be downloaded again unless you remove or reset the ProjectStreet@Car project. 
* When we update the app in the future, parts of the Docker container will be redownloaded, however, Docker is smart about only downloading the parts which have actually changed  (that's why we use it!). 


### Why is there no 32-bit support? ###
Docker only supports 64-bit processors. For those with 32-bit computers wishing to contribute to ProjectStreet@Car are sadly not supported.

### How does ProjectStreet@Car store Docker containers between jobs? ###
Docker containers which are downloaded by ProjectStreet@Car are saved to the file `scratch/boinc2docker_persist.tar` in the project folder. 


### How do I see the error log for my jobs? ###
{:#log}

Find the log by going to Community->Your Account->Tasks and searching for the task which failed. You'll see the log at the bottom of the page. 


### My *boinc2docker* jobs stop at 0.100% ###
When *boinc2docker* first starts, it downloads the Docker container needed to run the job. During this download (which will not show up in BOINC's "Download" tab), the progress bar will be pinned to 0.100%. 

The very first time you run a *boinc2docker* job the download may take a while, the container is about 35Mb. After that it is saved for all future jobs. Any time we update the app there may be smaller incremental downloads as well. 


### What is *boinc2docker*? ###
This is the name for the software which allows us to run Docker containers with BOINC. It can be used to run any code, *boinc2docker* being one of them. You can follow development of boinc2docker on [github](https://github.com/marius311/boinc2docker). 


### Can I see the source code of ProjectStreet@Car? ###
Absolutely! All of the code, including the *boinc2docker* code itself as well as the server code is publicly available on the [github page](https://github.com/Nordgedanken/ProjectStreet). In fact, the *exact* commit the server is currently running can be seen on the [server status](server_status.php) page. We run our server from a Docker container, so its super easy for anyone run a copy of our server too, and play around with modifying or seeing how it works. 


### Does it hinder ProjectStreet@Car if I abort jobs? ###
No, feel free to abort jobs if you need to. Our results are built up by the aggregate of all jobs, and losing any one particular result is fine. 
