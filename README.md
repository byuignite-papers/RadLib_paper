# PaperTemplate
A "fork-able" template for writing a paper via LaTeX

## How to Use this Repo to Write a Paper

Congratulations, you are preparing to write a paper!
Writing a paper is one of the most important parts of doing research.
It is how data gets transmitted to the scientific community and how you get credit for doing the work.
Good researchers start writing the paper while they are planning and executing their research.

Before you proceed, please read the short (3 page) [article](https://onlinelibrary.wiley.com/doi/epdf/10.1002/adma.200400767) (a copy is also in the notes/ directory) by George Whitesides on how to write a paper.
It is excellent and we will bascially follow the steps he outlines below.

It will probably also be useful for you to look at a few papers for examples of what do to.
One place to look is [our group publications](http://ignite.byu.edu/publications.html).
Focus on the structure of the papers, the way the sections are organized, instead of the actual contents of the paper.

### Fork the repository
First, fork this repository; a fork is simply a copy where you are the owner.
Since you want to be able to make changes and merge without my permission, and because you do not want to merge back into the template, please make a fork (as opposed to a branch).

### Become familiar with LaTeX
You should write all of your papers (and prospectus and proposals) in LaTeX.
If you are not already familiar with LaTeX, spend a few minutes learning about it.
There are many tutorials available online, but [this one](https://www.overleaf.com/learn/latex/Learn_LaTeX_in_30_minutes) by Overleaf is pretty good.
The [LaTeX wikibook](https://en.wikibooks.org/wiki/LaTeX) is also an excellent referece.

In addition, you will need a LaTeX editor to write your documents.
There are several choices:
- Command line. If you use Mac, or Linux (or Linux subsystem for Windows), you can simply use vim and the command line.
This gives you the most control but also has the largest learning curve.
You may need to [install texlive](https://www.latex-project.org/get/), if it isn't already installed.
- [Overleaf](https://www.overleaf.com/) is a web-based interface for using LaTeX.
This is essentially "Google Docs" for LaTeX.
It is currently very popular, but has a "freemium" subscription model.
Basically, you can use it for free, but the advanced features require paying.
- [Lyx](https://www.lyx.org/) is an easier option for using LaTeX if you don't want to use Overleaf, but you don't feel comfortable with the command line. It is available on Linux, Windows and Mac.

Most journals provide document classes for LaTeX that allow for easy submission.
The ACS uses the package [achemso](https://ctan.org/pkg/achemso?lang=en) and the APS uses [revtex](https://journals.aps.org/revtex).
The template provided here uses achemso, but it is relatively easy to switch if you need to.
Please use one of these packages unless you know better.

### Do a Literature Review
Before making an outline, you should spend some time thinking about how your work is situated within the literature.
Begin gathering the references you will need for your bibliography and store them in your preferred bibliography management software ([Jabref](http://www.jabref.org/), [Mendeley](https://www.mendeley.com/), [Endnote](https://endnote.com/), etc.).
To help you as you read the literature, make a "Literature Review" document (e.g. in OpenOffice or Word) to record a few thoughts (in your own words) about the papers you read.
Store these documents in the `notes` directory (see the given examples).

### Make an outline
As instructed by Whitesides, make an outline of your paper.
Do this in the LaTeX document `manuscript.tex` (see the document for additional help and instructions).
To make the outline, follow these steps:

1. Get out a blank piece of paper and write down, in any order, all the important ideas that you have concerning your paper.
These should include questions like "Why am I doing this work?", "What does it mean?", "What hypotheses am I testing?", "What results do I have or expect?", "What have others done?", "What is the prior state-of-the-art?"
As part of this process, *sketch out (by hand) all of the possible figures and schematics* that you have generated or will generate.

2. Organize your ideas into three main sections:

    I. Introduction (why did I do the work?)
    II. Results and Discussion (what did I do?)
    III. Conclusions (what does it mean?)

3. Take each of the sections and organize them on a finer scale.
Pay particular attention to how you organize the data and *figures*.
Think about the story you are telling and how the paper will make the most logical sense when put together.
*This may (and often does) include data you do not have or a figure you had not considered making previously*.
One reason to make an outline early is to anticipate these types of logical holes.

At this stage, you will want to type up your ideas in `manuscript.tex.`
Typically your outline will only be a couple of pages long, will include only a few complete paragraphs and will have only a few key references.
Put "placeholder figures" or scanned hand-drawings as stand-ins for the acutal figures you will make.
It takes a long time to make figures; do not spend the time at this point.
However, it is usually useful to add a caption that describes what the figure will contain.

4. Discuss your outline with your coauthors so that they can give their opinion, suggest changes and return for revisions.
This will likely require several iterations.

### Fill in your outline
Once your outline is complete, you are ready to take data and write your paper!
As noted by Whitesides, it is much more efficient to write your paper *while you take data.*
Having the paper you want to write in mind will help guide you to make good decisions about what calculations ("experiments") you need to run and what analysis you need to do.
As Whitesides says:
> Do not, under any circumstances, wait until the collection of data is 'complete' before starting to write an outline. 
> No project is ever complete and it saves enormous effort and much time to propose a plausible paper and outline as soon as you see the basic structure of a project.

## Directories

### codes
This directory should store the code or codes used to generate the raw data.
Typically this will be a copy of the simulation software you used.
Plotting scripts, (and some analysis scripts) will not normally be stored here.

### data
This directory can store (i) *raw* data and (ii) the post-processed data and accompanying analysis scripts.
This will complement the codes directory. If you have a lot of data, you might want to keep this elsewhere (see below), but include a README that details where to find the data.
Whether you store data here or elsewhere, do not store "garbage" data.
If you discover that the data is bad or that the runs have failed, please delete it.
(If you are still developing or debugging a code, you may have used some data that is useful but that may not fit with a paper.
Store this data in a separate directory that is clearly named.)

The all-important point is to be very clear and organized in your data structure so that it can be understood by you and others in the future. 
Include README files, use good file and folder names. Use a directory structure. For example, keep all real cases at a top level, but dump all other cases that you want to keep, but that are not used in the final work, in a subdirectory like "other_cases".

*Because this directory can hold a large amount of data, it will be ignored by the git repository.
More information about this directory and how it is backed up is detaled below.*

### figures
This directory stores the figures that will be in your paper or supplementary information.
This directory should not include analysis scripts or raw data, but rather should only include the data necessary to make plots.
Unlike the data directory, the figures directory *will* be stored in the git repository, so care should be taken about the size of files used here.

Each figure should be stored in a separate sub-directory inside figures. Name
the sub-directory the same as the figure name so that the directory name,
figure file name and LaTeX references are all the same.

Inside each figure sub-directory, you will have the figure data, and the figure
generating script, and the actual figure. The figure data may be generated
elsewhere and copied here. You should include appropriate documentation noting
locations and details in a README.  

You should make your files in a plotting tool that can draw publication quality
figures.  Python, Gnuplot and Matlab can all do this, but *Excel cannot*.
Figures will come in two general types: those that can be saved in a vector
format, and those to be saved in a raster format.  Line plots, like x-y scatter
plots, or bar charts, or line plots will be vector format, and should be saved
as .pdf files. Contour plots, volume renderings, or photographs are raster
plots and should be saved as .png files. 

If you need to draw something, i.e. make a schematic, you should use a vector drawing program like Inkscape or Adobe Illustrator.
Powerpoint can also do this, just save the image as a .pdf file.
(Do not use a bitmap drawing program like Gimp or Adobe Photoshop.)

### manuscript
This directory should contain:
- The manuscript LaTeX file: `manuscript.tex`
- The supplemental information LaTeX file: `suppinfo.tex` (if needed)
- The references .bib file: `references.bib`
- A copy of all of the figures in .pdf format

When you run pdfLaTeX on the manuscript.tex file (either on your machine or in Overleaf) you will generate a manuscript.pdf file with your figures.
A number of other files (e.g. `mauscript.log`, `manuscript.bbl`) will also be generated.
These latter files tell help LaTeX run or tell you what it did.
You can delete these if you want.
There is a package called [rubber](https://launchpad.net/rubber) that is convenient for automating the latex build.

### notes
This directory is a place for you to store any notes, files or scripts that you want tracked in the repository but that don't fit elsewhere in the directory structure.
This is an especially good place to store your notes on the literature search and bibliography.
A "literature review" document that summarizes the main points of important papers while reading is helpful.

### submissions
This directory is a place to track different stages of the revision process, including correspondence with co-authors and with journals.
For example, you typically need to write a cover letter to the editor of the journal when you submit the paper.
This directory is useful for storing these types of things.

## Storing Data

Every paper has raw data associated with it.
It is a good practice to store the raw data alongside the paper in a data/ directory. If the data is large, this might not be feasible.
Unfortunately, git isn't a very useful tool for storing data.
Every time you commit a replace a data file with a new one, it makes a copy, and this can end up generating huge repositories.
This is bad, because it then takes forever to clone, commit, push and pull from repos, and we end up having to pay GitHub to store our data.
We definitely don't want to do this, since we typically generate GBs (and sometimes TBs) of data!
To avoid this, follow this rule: **Do not store your raw data in a directory that is tracked via git**.

The "data/" directory (noted above) may hold your data, but its contents are not included when you commit or push your repository.
This is done via the .gitignore file inside the repository's main directory.
This ensures that you can store your data locally along with your paper, but keep it out of the git repository.
Again, as noted above, if your data is too large to store locally, include a README of the location that the data is archived.

### Archiving simulation data
* Simulations are often performed on a range of machines. Data generated should be carefully stored and archived.
* Simulation data is normally stored on scratch space when computed. This is short-term data and is subject to periodic purges.
* Supercomputing resources will have dedicated storage space for archiving simulation data. All data and code that goes into a paper should be cleaned, organized, and documented, and then stored on the archive space.
* Note that simulation data is not stored as part of the paper's git repository.

