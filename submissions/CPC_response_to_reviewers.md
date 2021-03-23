# Response to Reviewers: CPC initial submission

## Reviewer 1

This manuscript introduces “RadLib,” a C++ library to calculate absorption coefficients for use in radiative heat transfer calculations. The library has reasonable value to the research community, despite a few limitations in its scope and design. The library is self-contained (doesn’t have any external dependencies), which is convenient.

I have a number of comments on the manuscript as well as the software itself which the authors should consider to improve the manuscript and software.
Manuscript:
1.	There is no general user documentation provided in section 3. Figure 1 includes information that is more algorithmic than illustrative of the API.
2.	Section 5 makes several editorial claims that are quite subjective, and not well-supported:
a.	First sentence: “historically difficult to implement … complexity and high computational costs”
i.	Property evaluation is not the expensive part of a radiation calculation. Solving the RTE is the expensive part.
ii.	I wouldn’t characterize the property evaluation as particularly complex in comparison with other aspects of combustion simulations (kinetics, thermodynamics, transport properties).
b.	At the end of the first paragraph, the authors seem to imply that RadLib will solve the challenges of radiation modeling. Again, it is the RTE solver, not the property evaluation, that is the largest time-sink in terms of computer and human resources. 
c.	These kinds of statements persist throughout the second paragraph as well. There are limitations in RadLib such as lack of scattering treatment for particle-laden flows, inability to include more species, lack of any line-by-line capabilities, etc. The library checks a few useful boxes, but the verbiage here seems to take more credit than the authors may be due.
3.	Section 5 claims that “RadLib’s modular framework is designed to easily accommodate new models as well,” which is a bit of an overstatement. See comments below w.r.t. assumptions on species considered, hard-coded polynomial coefficients, etc. all of which reduce extensibility.
4.	There are several minor issues that need to be addressed:
a.	Abstract: “well-written” is subjective and should be removed.
b.	Introduction: second sentence: “Combustion simulations…” is a run-on sentence.
c.	Page 10: “[INSERT RUNTIME COMPARISONS HERE]”
d.	Section 7 heading: “Interes”
Software deficiencies & suggestions:
1.	API doxygen documentation is non-standard. It appears that the doxygen documentation is provided in the .cc files rather than the header files, which is where it is typically found. Downstream developers would typically be working from headers and the installed library, so it is convention to have doxygen documentation in the header only. This also reduces clutter in the implementation files.
2.	make_examples.sh:
a.	will only work with a g++ compiler in the user’s path.
b.	Is referred to as build_examples.sh in the README.md file
c.	is redundant with the cmake build system and isn’t portable. It should probably be removed.
3.	It appears that there are no tests associated with the library. This is a bit surprising - I would expect regression test coverage on the basic API functionality.
4.	CMake build system:
a.	Consider installing a “RadLib.cmake” file for downstream usage by CMake-based projects. This helps downstream build systems configure for RadLib usage (setting include paths, etc.).
b.	probably shouldn’t specify optimize or debug flags directly, as CMake will provide appropriate values on most platforms.
c.	the default build type isn’t defaulting to Release for me; it remains blank.
d.	I suggest not using verbose makefiles by default.
e.	Using GLOB to install the headers is not the appropriate CMake approach.
f.	the data files are not copied into the examples build directory, meaning that the example executables do not run.
i.	The run-examples.sh script is not helpful as it is not installed into the build directory where the executables are produced and doesn’t have path information to actually run the executables.
g.	Using “doxygen” as a target is not ideal since it conflicts with the “doxygen” executable name. It still works fine though...
5.	It appears that line-by-line data from HITEMP/HITRAN files cannot be loaded into RadLib. That’s an unfortunate limitation, but not a deal-breaker. 
6.	It looks like the software hard-codes Plank mean absorption coefficients as (fourth-order?) polynomial fits? Same for WSGG. There is no discussion of why this was chosen, how the coefficients were determined, or a characterization of its accuracy. Do you observe any problematic behavior with the fourth order polynomials over temperatures from 300 to 3000 K?  Are these interpolants or regression of data?
7.	The two previous items combined lead to a significant limitation of RadLib: one cannot easily add new species or modify existing data that is used to generate the absorption coefficients since there has been internal preprocessing of (an unknown subset of) the HITEMP/HITRAN databases to produce curve fits. And given that this process is opaque, it isn’t reproducible.
8.	RadLib only considers CO2 and H2O for WSGG, which is fairly limited. Even for Plank mean, only H2O, CO2, CO and CH4 are considered. NO and OH would be nice to include. It appears that including additional species would be a non-trivial undertaking.
9.	Documentation:
a.	Generating the documentation directly via doxygen v. 1.8.20 gives numerous warnings about obsolete tags and then fails because it is looking for a relative path “../../docs/doxygen” that doesn’t exist. This should be fixed.
b.	Generating the doxygen documentation via the build system target (“make doxygen”) does seem to work fine.


## Reviewer 2

A radiation spectral property library is developed in this study using C++. A Planck-mean absorption coefficient based model, a WSGG model and a RCSLM model from the literature are implemented  in the package. Verification results are presented and discussed. Although the authors addressed an important issue of radiation modeling, the contribution is marginal in the reviewer's opinion. No new models/methods are proposed in this study. As the authors correctly pointed out, the solver for radiative transfer equation is equally important, which is not included in the library. The coupling of a spectral model to a specific RTE solver, can have different levels of challenges depending on the combination. The design of the library doesn't really address any of the RTE-related issues, nor provide any new solutions to simplify the coupling of spectral models to RTEs. If the authors can demonstrate that the library can be coupled with popular CFD software and popular RTE
solvers such as P1 and DOM, it would further improve the quality of this study. A few other concerns are listed as follows:

1) RADCAL data were used to generate the PlanckMean absorption coefficient. Based on the reviewer's experience, the PlanckMean absorption coefficients can have meaningful differences when generated from RADCAL and from HiTEMP2010. It is recommended a more recent database being used for the library.
2) Page 10, missing information on [INSERT RUNTIME COMPARISONS HERE].
3) In Figure 2, the RCSLM seems to consistently perform better than WSGG, except in Example S2. In addition, WSGG performs worse than PM in Example S4. Can the authors explain why?
4) Equation 6 appears to be inaccurate.
5) Typo: page 4, line 49, "relating them" -> "relating the"

## Reviewer 3

The Computer Program in Physics (CPiP) submission titled, "RadLib: a radiative heat transfer model library for CFD" by Stephens et al reports a library of radiative property models that is modular and can be interfaced with other radiation model components. The manuscript is well-written and well-organized. The works cited are reasonable. RadLib contains a gray Planck-mean (PM) model, a weighted sum of gray gases (WSGG) model, and the rank-correlated SLW model. This is definitely an important tool for the combustion community, where the radiation modeling is often oversimplified mainly because of the lack of readily available appropriate radiation model libraries! I am not aware of any open-source libraries that combine the three property models presented here.
The models included in RadLib are already well-established and well-validated in the radiation community. The library is written in C++ and is supposed to work in any Linux-like system. The code is well commented, although the associated documentation needs to be improved (see major comment #1).

Considering all these, I think that this CPiP submission is definitely within the scope of the journal and of interest to the research community. However, the following concerns must be addressed before the submission is considered for publication.


1) I could not successfully build and run the library in two different Linux systems. In both cases, first, the cmake returned an error:
"CMake Error at c++/CMakeLists.txt:34 (install): install TARGETS given no ARCHIVE DESTINATION for static library target "radlib"."
I could resolve this by adding ARCHIVE DESTINATION line on the c++/CMakeLists.txt file.
But, then on during "make" my installation was interrupted several times because of missing packages in my Python installation.
I would strongly recommend that the authors modify the installation instructions to include: a) list of dependencies (i.e., what compilers, what versions of python, what python packages, etc.), b) how to install the dependencies before building RadLib, c) a way to build RadLib with either only C++ or only Python. These installation notes do not necessarily need to be in the main manuscript, but they must be in the installation README of the code package.

2) The library includes PM, one WSGG, and a RCSLW model. The authors should clearly indicate the rationale of these choices (i.e., why only these three models) early on in the manuscript. Since this is intended for researchers who, presumably, are not experts in radiation modeling, the inclusion of these three models can be misleading. One might think that these three models are the most appropriate models for their simulations.

3) RadLib is intended to be expanded with new radiation property models in the future and interfaced with a user-supplied solver module for RTE. A brief discussion on how to interface such an external solver module should be presented. There is an example of a ray-tracing solver presented in the code files, but a brief discussion on coupling one's own RTE solver is important in the manuscript. Additionally, a brief discussion on how a user can add a new radiative property model should also be included.

4) The Planck-mean absorption coefficient included in RadLib is based on TNF workshop data (from 2003). According to the references cited, these are fairly old correlations. If the authors use these data, I am concerned that the model parameters and correlations used in RadLib for the PM model may be obsolete and inaccurate. Can the authors please comment on this?

5) On page 13, the authors present a paragraph describing Figs. 2 and 3 - the comparison of various radiation property models present in RadLib in one-dimensional configurations. The comparisons are presented simply as observations without any explanation or reasoning why the models behave the way as seen in Fig. 2 and 3. If I understand correctly, the focus of the work presented here is not the comparison of the accuracy of the three models but to showcase the library. Therefore, these comparisons - specifically without any explanation of the results - may not be essential to the current manuscript, and can be shortened. These results do serve as descriptions of example cases provided in RadLib. On the same page, the authors say that "While ommitted [should be omitted] here for brevity, the implemented WSGG and RCSLW models give essentially identical results to those presented in [11, 14] such that these examples also serve as a validation of the implementation of the
models." The authors should avoid qualitative description such as "essentially identical" in the context of validation and present a quantitative (e.g., % error) metric wherever possible. A strong validation is important for programs like this.


6) The computational cost tables for two cases show a significantly different trend, which the authors attribute to "additional overhead required in performing the calculations." Can the authors be more specific as to what these overheads may be? They say that they have neglected the initialization and input/output costs. Also, do these CPU times presented include the cost for the ray-tracing solver as well? Are the grids kept the same for all configurations?

7) In line 53 on page 4, the authors claim to have CH4 property in RadLib but none of the validation cases contain CH4. Furthermore, for RCSLW, the refer to Pearson's work as a source for data of CO2, H2O, and CO without indicating the source data for CH4.

MINOR:

1) It should be clarified that RadLib only provides radiation properties for non-scattering media.

2) In the program summary the description of the nature of the program is somewhat confusing from a grammatical construction standpoint. Particularly, the following part, "This presents a problem for practitioners who wish to use/implement radiation models for which [refers to what?] such models consitute [constitute?] only a small but important part of a larger simulation.  Turbulent combustion simulations are one such example [example of what?].  Often, rudimentary assumptions [in what?] are made and this can negatively impact results."

3) In Page 2, "In some cases, radiative gains or losses are small compared to other energy sources or heat transfer modes and radiation can be safely neglected, ... difficult to simulate accurately without a robust radiation model." Please provide some references to support these arguments.

4) Please explain all the symbols used in equations. For example, eta in Eqn. 1 (and subsequent equations), Eb  in Eqn. 11.

5) Page, 4: "Global models are an important class of radiation property models that make use of spectrally-integrated radiation properties and are usually versions of the weighted sum of gray gases (WSGG) model [1, 2]." This sentence is somewhat misleading. It may be more appropriate to think of WSGG models as special cases of SLW or FSK models.

6) In lines 48-52 on Page 4, the authors say that the absorption coefficients are calculated using some correlations after some curve-fitting to spectroscopic databases. I am not sure what the authors refer to as correlations. There may be some correlations involved in WSGG models, but it is not clear to me where are correlations involved in RCSLW.

7) On page 7, the authors mention that the PM model can be "reasonably accurate" in some cases and go on to say that, "The Planck Mean model is most appropriate under optically thin conditions  with  relatively  low  radiative  transfer  relative  to  other  heat  sources such  as  reactive  heat  release  rates." The Planck Mean model will be appropriate in optically thin cases as there is very little reabsorption. This may or may not be connected with "relatively  low  radiative  transfer  relative  to  other  heat  sources." In fact, if the radiative heat transfer is much lower than chemical heat release, neglecting radiation altogether may also be reasonable! Although, the definition of "relatively low" is subjective.

8) On the same page, lines 40-41, "This version of  the  WSGG  model  is  advantageous  because  it  allows  for  arbitrary  CO2 and  H2O  compositions,  increasing  its  accuracy  and  flexibility." Can the authors provide some references that show the increased accuracy and/or flexibility of this WSGG over any other WSGG?
9) With respect to Eqn 8, Mr is defined as molar ratio y_H2O/y_CO2. Are the authors using y as a symbol for mole fraction rather than mass fraction as is conventionally done?

10) Please remove the words "[INSERT RUNTIME COMPARISONS HERE]" on Page 10.

11) In lines 29-30 on page 13, please insert the units for Q in -80 and 200.

12) In the Discussion (page 16), the authors write, "Neglecting radiation or using simple models like the optically thin assumption is adequate for some cases with simple geometry or limited chemical reactions…" This can be misleading. I am not sure if either the simple geometry or the limited chemical reactions give any indication of the importance of radiation. Rather, something like a radiant fraction or optical thickness may be a more appropriate metric to justify neglecting radiation or using an optically thin model.
