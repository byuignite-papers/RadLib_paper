# Response to Reviewers: CPC initial submission

## Reviewer 1

This manuscript introduces “RadLib,” a C++ library to calculate absorption coefficients for use in radiative heat transfer calculations. The library has reasonable value to the research community, despite a few limitations in its scope and design. The library is self-contained (doesn’t have any external dependencies), which is convenient.

I have a number of comments on the manuscript as well as the software itself which the authors should consider to improve the manuscript and software.

**The authors would like to thank the reviewer for their time and knowledge. While we disagree with some of the reviewer's comments and suggestions, they are, overall, constructive and helpful to the paper's development.**

### Manuscript:

1. There is no general user documentation provided in section 3. Figure 1 includes information that is more algorithmic than illustrative of the API.

	**Section 3 has been revised and extended to include more information on how users can include and interact with the RadLib library, including explicit references to example files that further illustrate usage of the library.**

2. Section 5 makes several editorial claims that are quite subjective, and not well-supported:
	1. First sentence: “historically difficult to implement … complexity and high computational costs”
		-Property evaluation is not the expensive part of a radiation calculation. Solving the RTE is the expensive part.
        	-I wouldn’t characterize the property evaluation as particularly complex in comparison with other aspects of combustion simulations (kinetics, thermodynamics, transport properties).

    2. At the end of the first paragraph, the authors seem to imply that RadLib will solve the challenges of radiation modeling. Again, it is the RTE solver, not the property evaluation, that is the largest time-sink in terms of computer and human resources. 

    3. These kinds of statements persist throughout the second paragraph as well. There are limitations in RadLib such as lack of scattering treatment for particle-laden flows, inability to include more species, lack of any line-by-line capabilities, etc. The library checks a few useful boxes, but the verbiage here seems to take more credit than the authors may be due.
    
    **The authors have a number of concerns about the reviewer's claims here that they would like to address. First, note that the subject of the first sentence of Section 5 is "radiative heat transfer models", which does not refer specifically to either radiation property models or RTE evaluation methods, but the treatment of computational radiative heat transfer as a whole. This generalization holds for the entire first paragraph of Section 5. Additionally, at no point in the paper do the authors claim that property evaluation is more complex or computationally expensive than the RTE solution, only that it "can be a difficult and time-consuming portion of radiation calculations" (pg. 2). Likewise, the paper contains no claims about the complexity of radiation property models in relation to other aspects of combustion simulations. (On this topic, however, the authors would like to point out that these other aspects of combustion simulations are typically well-characterized in both commercial and open-source CFD codes and do not require very much user interaction, whereas radiation modeling is often absent or highly simplified.) The second paragraph of Section 5 is a brief discussion on how RadLib can benefit researchers that draws from the authors' experiences. It does not claim that RadLib will solve any of the challenges of radiation modeling, only that it can "ease . . . obstacles", which the authors believe it can do.**
    
    **All of that said, however, the fact that the reviewer made these assumptions and pointed out these implications indicates that the paper's language is, in fact, too subjective. Even though none of these statements were explicitly made, they must be implied for the reviewer to come to these conclusions. As such, revisions have been made throughout the paper to reduce subjective language, support generalized statements with additional explanation and/or references, and include due discussion of RadLib's limitations.** 

3. Section 5 claims that “RadLib’s modular framework is designed to easily accommodate new models as well,” which is a bit of an overstatement. See comments below w.r.t. assumptions on species considered, hard-coded polynomial coefficients, etc. all of which reduce extensibility.

	**In order to avoid subjective language, this sentence has been revised as follows: "RadLib's modular framework can also accomodate new models, . . .". Specific extensibility issues are addressed below with their respective reviewer comments.**

4. There are several minor issues that need to be addressed: 
	1. Abstract: “well-written” is subjective and should be removed. 

		**The offending sentence (actually located in the "Solution method" section of the Program Summary) has been revised to eliminate subjective language.**
	
	2. Introduction: second sentence: “Combustion simulations…” is a run-on sentence.	
	
		**Technically, no, this is not a run-on sentence, but its structure is awkward and inhibits readability. It has been revised to the following: "For example, combustion simulations are often complicated by the need for accurate radiation modeling, which can be difficult to implement and computationally expensive relative to overall simulation cost."**
	
    3. Page 10: “[INSERT RUNTIME COMPARISONS HERE]”
    
		**This was a placeholder that should not have been included in the document. It has been removed.**
	
	4. Section 7 heading: “Interes”
	
		**Fixed section heading. Now correctly reads "Declaration of Competing Interests".**

### Software deficiencies & suggestions:

1. API doxygen documentation is non-standard. It appears that the doxygen documentation is provided in the .cc files rather than the header files, which is where it is typically found. Downstream developers would typically be working from headers and the installed library, so it is convention to have doxygen documentation in the header only. This also reduces clutter in the implementation files.

	**The authors were previously unaware of any such standards or conventions, and follow up research indicates that this is a stylistic preference rather than a flaw in the software. The locations of doxygen documentation blocks were chosen for overall readability as they tended to clutter the header files and were less obtrusive when located in the implementation files. However, the reviewer does make a valid point regarding usage by downstream developers, and while we would expect the typical RadLib user to be comfortable working with both header files and source code, it is worthwhile to consider all possible usages. Because this is an issue of style rather than function, no immediate changes have been made to the code or its documentation, but the authors appreciate this information about standard practice and will consider its implications moving forward.**

2. make_examples.sh:
    1.	will only work with a g++ compiler in the user’s path.
    1.	Is referred to as build_examples.sh in the README.md file
    1.	is redundant with the cmake build system and isn’t portable. It should probably be removed.

	**The make_examples.sh file has been removed.**
	
3. It appears that there are no tests associated with the library. This is a bit surprising - I would expect regression test coverage on the basic API functionality.

**TO DO: consult Josh about appropriate tests for RadLib**

5. CMake build system:
    1.	Consider installing a “RadLib.cmake” file for downstream usage by CMake-based projects. This helps downstream build systems configure for RadLib usage (setting include paths, etc.).
    1.	probably shouldn’t specify optimize or debug flags directly, as CMake will provide appropriate values on most platforms.
    1.	the default build type isn’t defaulting to Release for me; it remains blank.
    1.	I suggest not using verbose makefiles by default.
    1.	Using GLOB to install the headers is not the appropriate CMake approach.
    1.	the data files are not copied into the examples build directory, meaning that the example executables do not run.
    1.	The run-examples.sh script is not helpful as it is not installed into the build directory where the executables are produced and doesn’t have path information to actually run the executables.
    3.	Using “doxygen” as a target is not ideal since it conflicts with the “doxygen” executable name. It still works fine though...

		**Build target name has been changed from "doxygen" to "docs" for safety.**

5. It appears that line-by-line data from HITEMP/HITRAN files cannot be loaded into RadLib. That’s an unfortunate limitation, but not a deal-breaker. 

	**At present, RadLib's models cannot accommodate such data input, but this is a limitation of the models themselves, not the software. The appropriate line-by-line data is included within the RadLib package, which the authors consider a convenience rather than a hindrance. The ability to load database files directly into RadLib could be useful to researchers looking to extend RadLib's model library to include modern spectral models, however. The authors appreciate the suggestion and will consider it for future development.**

6. It looks like the software hard-codes Plank mean absorption coefficients as (fourth-order?) polynomial fits? Same for WSGG. There is no discussion of why this was chosen, how the coefficients were determined, or a characterization of its accuracy. Do you observe any problematic behavior with the fourth order polynomials over temperatures from 300 to 3000 K?  Are these interpolants or regression of data?

	**This discussion was purposely omitted because it does not align with the goal of the paper, which is to present RadLib as a software tool for calculating radiation property data, not to evaluate or compare the included models. All of the reviewer's questions are addressed in detail in the referenced literature (Planck Mean coefficients in [3,5] and WSGG in [10,11]). The authors believe that this is an issue of scope rather than missing information but are willing to extend the discussion at the editor's discretion.**

7. The two previous items combined lead to a significant limitation of RadLib: one cannot easily add new species or modify existing data that is used to generate the absorption coefficients since there has been internal preprocessing of (an unknown subset of) the HITEMP/HITRAN databases to produce curve fits. And given that this process is opaque, it isn’t reproducible.

	**The authors acknowledge that modifying existing models in RadLib is non-trivial, but would like to note that the paper does not claim that the implemented models are easily modified, only that the RadLib framework can be used to implement and validate additional models. Additionally, the authors disagree with the reviewer's statement regarding opacity and reproducability. The referenced literature (see above) clearly outlines the data sources and preprocessing methods applied; this information was omitted from the current paper for the reasons stated above. Given the provided sources, the process is neither opaque nor non-reproducible.**

8. RadLib only considers CO2 and H2O for WSGG, which is fairly limited. Even for Plank mean, only H2O, CO2, CO and CH4 are considered. NO and OH would be nice to include. It appears that including additional species would be a non-trivial undertaking.

	**All WSGG correlations consider only CO2-H2O mixtures with the exception of specialized subset of WSGG models that consider CO2-H2O-soot mixtures. This WSGG model was chosen for RadLib due to its popularity, relative simplicity, and good performance. RadLib implements the WSGG model presented by Bordbar et al. in references [10] and [11], which was developed specifically for use in oxy-fired combustion simulations. CO2 and H2O are the major products of all combustion processes, and CO is a major product of rich combustion. NO and OH are minor species that, while important to other aspects of combustion processes, do not typically participate significantly in radiative heat transfer processes. For more information, please refer to Section 20.6 of reference [2] and/or Section 3.4.1 of *Radiative Heat Transfer in Turbulent Combustion Systems* by Modest and Haworth.** 

	**It should also be noted that the Planck Mean absorption coefficients model as implemented in RadLib refers specifically to the radiation model in [3,5], which is one of the most common radiation models applied to turbulent combustion simulations. This is why Section 2.1 explicitly references the TNF radiation model and its calculated Planck Mean absorption coefficients. As implemented, the model is not intended to be general or extensible to other gas species and was never presented as such. Adding additional species would indeed be a non-trivial undertaking, but that is neither the goal nor purpose of RadLib as a software package, which presents and validates models rather than evaluating them.**

9. Documentation:
    1.	Generating the documentation directly via doxygen v. 1.8.20 gives numerous warnings about obsolete tags and then fails because it is looking for a relative path “../../docs/doxygen” that doesn’t exist. This should be fixed.
    1.	Generating the doxygen documentation via the build system target (“make doxygen”) does seem to work fine.

	**Build process has been updated so that documentation can be generated by the system target or manually.**

## Reviewer 2

A radiation spectral property library is developed in this study using C++. A Planck-mean absorption coefficient based model, a WSGG model and a RCSLM model from the literature are implemented  in the package. Verification results are presented and discussed. Although the authors addressed an important issue of radiation modeling, the contribution is marginal in the reviewer's opinion. No new models/methods are proposed in this study. As the authors correctly pointed out, the solver for radiative transfer equation is equally important, which is not included in the library. The coupling of a spectral model to a specific RTE solver, can have different levels of challenges depending on the combination. The design of the library doesn't really address any of the RTE-related issues, nor provide any new solutions to simplify the coupling of spectral models to RTEs. If the authors can demonstrate that the library can be coupled with popular CFD software and popular RTE solvers such as P1 and DOM, it would further improve the quality of this study. A few other concerns are listed as follows:

**The authors would like to thank the reviewer for their comments and suggestions. We have already begun working on coupling RadLib to CFD software (that includes a DOM model for the RTE solution, among other features) in order to demonstrate RadLib's capabilities.**

**TO DO: couple RadLib to ODT for demonstration purposes**

1. RADCAL data were used to generate the PlanckMean absorption coefficient. Based on the reviewer's experience, the PlanckMean absorption coefficients can have meaningful differences when generated from RADCAL and from HiTEMP2010. It is recommended a more recent database being used for the library.

	**The Planck Mean absorption coefficients model as implemented in RadLib refers specifically to the radiation model in [3,5], which is one of the most common radiation models applied to turbulent combustion simulations. It was chosen because of its popularity and widespread use in combustion simulations (despite its limitations). That said, there is value in using the most current tools. Given the reviewer's experience with variance in the Planck Mean absorption coefficients as calculated from various databases, the authors will strongly consider adding an updated Planck Mean model using the most current available data.**

2. Page 10, missing information on [INSERT RUNTIME COMPARISONS HERE].

	**This was a placeholder statement that should not have been included in the document. It has been removed.**
	
3. In Figure 2, the RCSLM seems to consistently perform better than WSGG, except in Example S2. In addition, WSGG performs worse than PM in Example S4. Can the authors explain why?

	**The PM and WSGG models are primarily empirical and contain very little representative physics, which could explain their unexpected behavior in Examples 2 and 4 but also makes it very difficult to find or treat sources of error. Any model, but especially empirical models, can behave unexpectedly when applied to conditions or parameters outside of those for which it was developed. The example cases are meant to be illusrative of the software's capabilities, not an evaluation of the models themselves, which is outside the scope of this paper. The reviewer's request for an explanation, however, is valid. A brief discussion has been added to Section 5 to address these specific discrepancies. Additional information about the specific limitations, strengths, and weaknesses associated with each model can be found in Section 2.** 

4. Equation 6 appears to be inaccurate.

	**Upon review, the authors find no errors in Equation 6, which matches Equation 20.65 of the general band model (of which the WSGG model is a subset) derivation in [2] and appears to be consistent with the other equations in the paper.**

5. Typo: page 4, line 49, "relating them" -> "relating the"

	**The phrase has been amended to ". . .using correlations relating them to local properties such as. . .".**

## Reviewer 3

The Computer Program in Physics (CPiP) submission titled, "RadLib: a radiative heat transfer model library for CFD" by Stephens et al reports a library of radiative property models that is modular and can be interfaced with other radiation model components. The manuscript is well-written and well-organized. The works cited are reasonable. RadLib contains a gray Planck-mean (PM) model, a weighted sum of gray gases (WSGG) model, and the rank-correlated SLW model. This is definitely an important tool for the combustion community, where the radiation modeling is often oversimplified mainly because of the lack of readily available appropriate radiation model libraries! I am not aware of any open-source libraries that combine the three property models presented here. The models included in RadLib are already well-established and well-validated in the radiation community. The library is written in C++ and is supposed to work in any Linux-like system. The code is well commented, although the associated documentation needs to be improved (see major comment #1).

Considering all these, I think that this CPiP submission is definitely within the scope of the journal and of interest to the research community. However, the following concerns must be addressed before the submission is considered for publication.

**The authors would like to thank the reviewer for their insightful comments and suggestions. As members of the combustion community, we heartily agree that a tool like RadLib could benefit researchers and facilitate radiation model development for combustion CFD.**

1) I could not successfully build and run the library in two different Linux systems. In both cases, first, the cmake returned an error:
"CMake Error at c++/CMakeLists.txt:34 (install): install TARGETS given no ARCHIVE DESTINATION for static library target "radlib"."
I could resolve this by adding ARCHIVE DESTINATION line on the c++/CMakeLists.txt file.
But, then on during "make" my installation was interrupted several times because of missing packages in my Python installation.
I would strongly recommend that the authors modify the installation instructions to include: a) list of dependencies (i.e., what compilers, what versions of python, what python packages, etc.), b) how to install the dependencies before building RadLib, c) a way to build RadLib with either only C++ or only Python. These installation notes do not necessarily need to be in the main manuscript, but they must be in the installation README of the code package.

2) The library includes PM, one WSGG, and a RCSLW model. The authors should clearly indicate the rationale of these choices (i.e., why only these three models) early on in the manuscript. Since this is intended for researchers who, presumably, are not experts in radiation modeling, the inclusion of these three models can be misleading. One might think that these three models are the most appropriate models for their simulations.

	**Section 2 has been heavily revised to address this issue. Each model's description now also includes a discussion of its strengths, weaknesses, and limitations when applied to combustion CFD in addition to the authors' rationale in choosing them for RadLib.**

3) RadLib is intended to be expanded with new radiation property models in the future and interfaced with a user-supplied solver module for RTE. A brief discussion on how to interface such an external solver module should be presented. There is an example of a ray-tracing solver presented in the code files, but a brief discussion on coupling one's own RTE solver is important in the manuscript. Additionally, a brief discussion on how a user can add a new radiative property model should also be included.

	**Section 3 has been revised and extended to include more information on how users can include and interact with the RadLib library, including explicit references to example files that further illustrate usage of the library. Adding additional radiative property models to the RadLib library, however, is nontrivial, and we chose to move its discussion to the package documentation so as not to clutter the manuscript. This can be changed, if necessary, at the editor's discretion.**

4) The Planck-mean absorption coefficient included in RadLib is based on TNF workshop data (from 2003). According to the references cited, these are fairly old correlations. If the authors use these data, I am concerned that the model parameters and correlations used in RadLib for the PM model may be obsolete and inaccurate. Can the authors please comment on this?

	**The authors purposely chose the TNF workshop data for calculating Planck Mean absorption coefficients because it is one of the most common and widely used radiation models applied to turbulent combustion simulations, despite its age and limitations. Section 2.1 has been revised to include a more explicit dicsussion of why the TNF radiation model was chosen and concerns related to its relative age and limited applicability. Section 4 includes example cases that clearly demonstrate the deficiencies of the PM model compared to the other models included with RadLib, and some additional discussion is available there.**

5) On page 13, the authors present a paragraph describing Figs. 2 and 3 - the comparison of various radiation property models present in RadLib in one-dimensional configurations. The comparisons are presented simply as observations without any explanation or reasoning why the models behave the way as seen in Fig. 2 and 3. If I understand correctly, the focus of the work presented here is not the comparison of the accuracy of the three models but to showcase the library. Therefore, these comparisons - specifically without any explanation of the results - may not be essential to the current manuscript, and can be shortened. These results do serve as descriptions of example cases provided in RadLib. On the same page, the authors say that "While ommitted [should be omitted] here for brevity, the implemented WSGG and RCSLW models give essentially identical results to those presented in [11, 14] such that these examples also serve as a validation of the implementation of the
models." The authors should avoid qualitative description such as "essentially identical" in the context of validation and present a quantitative (e.g., % error) metric wherever possible. A strong validation is important for programs like this.

	**While it is true that the purpose of this paper is to present the RadLib library rather than evaluate or compare the models, the authors believe that example case results in Figures 2 and 3 are important to the illustration of RadLib's capabilities. The reviewer's point about presentation without explanation, however, is valid; to that end, the discussion in Section 5 has been expanded somewhat to acknowledge, if not fully explain or provide cause for, various features and descrepancies in the example case results. Due to the empirical nature of the PM and WSGG models, it is very difficult to identify, explain, or rectify unexpected behavior. It should be noted, however, that any model, and especially empirical models, can behave unpredictably when applied to parameter ranges or conditions outside of those for which is was developed.**
	
	**In regards to validation, the authors are unclear as to what the reviewer expects to see. RadLib's model implementations give results that are, in fact, essentially identical to those presented in the literature to within any visual margin. We do not have access to the data used to generate the plots in the literature, without which any quantitative measure of error is meaningless. We do, however, compare model results to the line-by-line data, which amounts to a direct solution of the RTE and is also identical to the line-by-line data in the literature (as expected). The authors believe that this serves as adequate validation of RadLib's model implementations given the lack of originial data for comparison.**

6) The computational cost tables for two cases show a significantly different trend, which the authors attribute to "additional overhead required in performing the calculations." Can the authors be more specific as to what these overheads may be? They say that they have neglected the initialization and input/output costs. Also, do these CPU times presented include the cost for the ray-tracing solver as well? Are the grids kept the same for all configurations?

	**Section 4.1 already includes details of the computational cost calculations presented in Figure 4. The left hand plot (a) refers to one million evaluations of the absorption coefficients directly, while the right hand plot (b) refers to the cost to evaluate Example S3, which, like all of the example cases described in the first paragraph of Section 4, includes the ray-tracing solver. The quoted sentence has been revised to specify that the ray-tracing solver is primarily responsible for the additional overhead. Grids are identical for each configuration. Note that the RadLib library does not generate or manipulate grids as it is not involved in the RTE solution. The ray-tracing solver used in the example cases is provided for convenience and demonstration purposes.**

7) In line 53 on page 4, the authors claim to have CH4 property in RadLib but none of the validation cases contain CH4. Furthermore, for RCSLW, the refer to Pearson's work as a source for data of CO2, H2O, and CO without indicating the source data for CH4.

	**CH4 is present only in the PM model sourced from the TNF Workshop [3,5], which includes CH4 absorption coefficients because most of the TNF Workshop target flames are fueled by Ch4. In general, CH4 is not a significant radiatively participating species in combustion systems, but it is included for completeness.**

MINOR:

1) It should be clarified that RadLib only provides radiation properties for non-scattering media.

	**This clarification has been made explicitly in Section 2 and now appears throughout the text where appropriate.**

2) In the program summary the description of the nature of the program is somewhat confusing from a grammatical construction standpoint. Particularly, the following part, "This presents a problem for practitioners who wish to use/implement radiation models for which [refers to what?] such models consitute [constitute?] only a small but important part of a larger simulation.  Turbulent combustion simulations are one such example [example of what?].  Often, rudimentary assumptions [in what?] are made and this can negatively impact results."

	**The program summary has been rewritten for clarity.**

3) In Page 2, "In some cases, radiative gains or losses are small compared to other energy sources or heat transfer modes and radiation can be safely neglected, ... difficult to simulate accurately without a robust radiation model." Please provide some references to support these arguments.

	**References have been added throughout to bolster weakly supported arguments. Note that the quoted statement and related discussion has been moved to Section 5 due to unrelated revisions.**

4) Please explain all the symbols used in equations. For example, eta in Eqn. 1 (and subsequent equations), Eb  in Eqn. 11.

	**Text surrounding equations has been revised throughout to ensure explicit definitions of variables.**

5) Page, 4: "Global models are an important class of radiation property models that make use of spectrally-integrated radiation properties and are usually versions of the weighted sum of gray gases (WSGG) model [1, 2]." This sentence is somewhat misleading. It may be more appropriate to think of WSGG models as special cases of SLW or FSK models.

	**The authors agree that this statement could be potentially misleading. The second half of the sentence (beginning with ". . .and are usually. . .") has been removed.**

6) In lines 48-52 on Page 4, the authors say that the absorption coefficients are calculated using some correlations after some curve-fitting to spectroscopic databases. I am not sure what the authors refer to as correlations. There may be some correlations involved in WSGG models, but it is not clear to me where are correlations involved in RCSLW.

	**The RCSLW model's key tool is the absorption line blackbody distribution function (ALBDF), which is calculated using sppectral data available from databases like HITEMP. This is discussed briefly at the end of Section 2.3 on pages 8-9. For more information on how spectral data is used to calculate the ALBDFs, please see reference [22].**

7) On page 7, the authors mention that the PM model can be "reasonably accurate" in some cases and go on to say that, "The Planck Mean model is most appropriate under optically thin conditions  with  relatively  low  radiative  transfer  relative  to  other  heat  sources such  as  reactive  heat  release  rates." The Planck Mean model will be appropriate in optically thin cases as there is very little reabsorption. This may or may not be connected with "relatively  low  radiative  transfer  relative  to  other  heat  sources." In fact, if the radiative heat transfer is much lower than chemical heat release, neglecting radiation altogether may also be reasonable! Although, the definition of "relatively low" is subjective.

	**These statements regarding PM absorption coefficients are generally true. In combustion simulations, low radiative heat transfer relative to other heat sources, including chemical heat release and convective heat transfer, usually does, in fact, indicate very low radiative reabsorption rates. Sectiom 2.1 has been revised to clarify this connection. The quoted sentence now reads as follows: "The Planck Mean model is most appropriate under optically thin conditions in which low radiative transfer relative to other heat sources, including but not limited to chemical heat release and buoyancy-driven convection in combustion systems, indicates that very little radiative reabsorption is occuring."**
	
8) On the same page, lines 40-41, "This version of  the  WSGG  model  is  advantageous  because  it  allows  for  arbitrary  CO2 and  H2O  compositions,  increasing  its  accuracy  and  flexibility." Can the authors provide some references that show the increased accuracy and/or flexibility of this WSGG over any other WSGG?

	**Two references for the chosen WSGG model are given earlier in the paragraph. The second (Bordbar et al. 2020) includes detailed comparisons between this model, its immediate predecessor (see Bordbar et al. 2014), five other WSGG models, and line-by-line calculations for four different test cases that show high accuracy over a wide range of molar ratio values. While other models may have performed better in individual tests, this model demonstrated consistent accuracy over a range of scenarios. For clarity, this reference has been added to the end of the aforementioned sentence so as to better indicate where to obtain relevant information.**

10) With respect to Eqn 8, Mr is defined as molar ratio y_H2O/y_CO2. Are the authors using y as a symbol for mole fraction rather than mass fraction as is conventionally done?

	**This is correct. The molar ratio was defined using these variables by Bordbar et al. [10,11] for the WSGG model and have been retained for consistency.**

10) Please remove the words "[INSERT RUNTIME COMPARISONS HERE]" on Page 10.

	**This was a placeholder that should not have been included in the document. It has been removed.**

11) In lines 29-30 on page 13, please insert the units for Q in -80 and 200.

	**Appropriate units have been added to the specified values.**

12) In the Discussion (page 16), the authors write, "Neglecting radiation or using simple models like the optically thin assumption is adequate for some cases with simple geometry or limited chemical reactions…" This can be misleading. I am not sure if either the simple geometry or the limited chemical reactions give any indication of the importance of radiation. Rather, something like a radiant fraction or optical thickness may be a more appropriate metric to justify neglecting radiation or using an optically thin model.

	**This issue was partially addressed in the discussion above (see point 7). In combustion simulations, things like simple geometry and small domain sizes limit the extent of any chemical heat release or convective heat transfer, which usually indicates that radiative heat transfer plays a more prominent role than it would otherwise. In order to clarify this association, the sentence in question has been revised to read as follows: "Neglecting radiation or using simple models like the Planck Mean model is adequate for some cases with simple geometry or limited chemical heat release, which are usually associated with optical thinness and low rates of radiative reabsorption, but most combustion simulations of interest to engineers and researchers require more advanced radiation modeling to yield accurate results."**
