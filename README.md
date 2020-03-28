# Untitled RadLib paper

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
