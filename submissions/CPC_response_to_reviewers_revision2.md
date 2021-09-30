# Response to Reviewers: CPC initial submission

Note, reviewer comments are included with responses in **bold** text.

## Reviewer 2

The authors have adequately addressed the reviewer's concern and significantly improved the quality of the manuscript
and the software. The reviewer recommends acceptance for publication.

**The authors thank the reviewer for their time and contributions.**

-------------------------------------

## Reviewer 3

The authors have responded to this reviewer's comments and have revised the manuscript substantially. There are still a
few issues that need to be resolved before it is accepted for publication.

**The authors thank the reviewer for their time and contributions.**

<font color='green'>
1) The capabilities and limitations of RadLib should be more clearly articulated. For example, different property models
   have different temperature ranges of applicability. While the authors specified what happens if the simulation
   temperature goes beyond the appropriate temperature range, they should comment or provide some recommendations on the
   appropriateness of the choice of the property model. For example, WSGG model has a valid temperature range of
   300-2400 K, and RadLib caps the absorption coefficient values at the respective bound if the simulation temperature
   is beyond this range. Can the authors provide some guidance on what is the error expected from such a strategy of
   allowing simulation to continue at ranges beyond the valid range of the property model? If the user knows that the
   simulation temperature is beyond 2400 K, is it recommended to use WSGG? Also, what is the applicable range of
   pressure in the models implemented? Related to this, on repeated readings, this reviewer felt a table to list the
   range of applicability for each model may be useful for understanding the capabilities of RadLib at-a-glance for an
   user.


   **Valid temperature ranges for the WSGG and RCSLW models were noted in their respective sections, and the applicable
   temperature range for the PM model has been added to its section. Additionally, the RCSLW model section specifies the
   range of pressures under which the RCSLW model can be applied. The WSGG model has pressure ranges given as the pressure-path length product, which are now    noted in the paper. A table summarizing these conditions has been added to the beginning of Section 2 as requested. 
   The models included cannot be used reliably outside the temperature and pressure bounds for which the models were developed. In the WSGG model, only the a weights have temperature dependence. The model gives a continuing trend as the temperature crosses above the 2400 K bound, up to at least 3000 K, suggesting use of the model up to 3000 K. This is true for the applicable range of Mr. However, some of the a weights are slightly negative above 2800 K as the upper Mr bound is approached. A statement is added to the paper.**


2) Please rephrase and, if possible, simplify the sentence on lines 82-86 ("Radiation property models, including those
   implemented in RadLib, are typically developed using ... correlations and modeling assumptions [4].") It is difficult
   to understand what exactly the authors are trying to convey in this sentence.

   **This sentence has been rephrased as requested.**


3) Line 92 - 95: "Modern band models .. cant lose accuracy when applied to nonhomogeneous media and may still require
   large numbers of RTE evaluations [1]." Should this be "<can> lose accuracy when applied …"?

   **Yes, it should, this typo has been fixed.**

4) In Figure 2, Example S5: Do "n=2" "n=4", etc mean the number of bands in RCSLW? It needs to be clarified.
   Furthermore, can the authors comment on the physical significance of RCSLW n =1 and how is this different from PM
   which uses a spectral average value?

   **The "n=2", etc. refer to the number of gray gases in the RCLSW model. The figure's caption has been updated to clarify this. The figure legend has also been modified to add "n=" to the number listed in Example S2.
The PM model differs from the $n=1$ RCSLW model as follows. The PM model gives a Planck-function-weighted average absorption coefficient, which is not true for the RCSLW model. That statement is now added to the paper in Section 2.1. For n=1, the RCSLW model considers one gray gas as well as a clear gas representing windows in the distribution, discussed on page 4 during the derivation of the gray gas spectral RTE (Eq. 5). 
We have revised the paper to note that the PM model does not include a clear gas. 
The PM model uses a linear mixing of partial-pressure-weighted components for the absorption coefficients, whereas the RCSLW model uses the multiplication method to get the mixture ALBDF from the product of species ALBDF values (Eq. 14), which is then used to compute the absorption coefficient and weight. The method of calculation of the gas absorption coefficient and weight for RCSLW follows from the summary description near the end of section 2.3.**
</font>

<font color='green'>

5) In Figure 2: This is a kind of cosmetic request, but still if the legends and symbols can be made consistent it will
   be easier to read.

   **We have revised the figure as requested. All subplots now use consistent line styles. Figure 3 is also made consistent with Fig. 2.**

6) In lines 499-501: Please clarify the sentence, "The PM absorption coefficient is 27.4 atm−1 m−1 , which results in a
   calculated optical thicknesses of 0.09 and 0.36 m in the thick and thin layers, respectively." Optical thickness is a
   dimensionless quantity, it cannot be 0.36 m. The thicknesses of layers are changing in S2, so what do these 0.09 and
   0.36 refer to?

    **These numbers are the inverse of the PM absorption coefficient times the partial pressures of the radiating gas (CO2) in the two regions and could be considered optical path lengths. We have corrected this issue in the paper and reword to "The PM absorption coefficient is 27.4 (1/atm*m), which results in optical thicknesses greater than 5.5
for the domain sizes considered in Example S2."**
</font>

<font color='green'>

7) In Section 5.1, please clarify which files and functions belong to FDS and which to RadLib. For example, in line
   544, "This was done by editing the radi.f90 file." By looking at the f90 extension the readers can guess that
   radi.f90 is part of FDS and not RadLib. But then in the next sentence, there are references to A_WSGG and KAPPA_WSGG
   functions. Are these part of FDS?

   **This sentence has been revised to clarify which files and functions belong to FDS.**

8) In lines 562-564: "The FDS default model uses a single gray gas with a composition and temperature dependent
   absorption coefficient computed from RADCAL." Is this equivalent to the PM model in RadLib? If so, a comparison with
   PM from RadLib and FDS default will be a good validation. Also, what RTE solver does FDS default use?

   **No, they are not equivalent. FDS uses the RadCal narrow-band model that depends on a user-specified radiative path length with a default value of 0.1 m. This is a geometry-dependent property that is different than a PM coefficient. For the radiative solver, FDS uses a finite-volume discrete ordinates RTE solver. That is noted in the paper in the first paragraph of Section 5.1. We added a note of the path length variable in the revised manuscript.**
</font>

9) In Section 5.2 can the author comment on the computational cost of RadLib-coupled FDS runs? Some quantitative
   information on the computational cost of using RadLib for a coupled run will be very useful. For example, the authors
   can compare the cost of the same FDS configuration simulated without any radiation, with RadLib, and with the
   FDS-default model.

<font color='green'>

10) Line 624: "At present, it includes three major radiation property models - Planck Mean (PM) absorption coefficients
    using the optically thin approximation, the weighted sum of gray gases (WSGG) model,..." PM can be used with any RTE
    solver in principle, not just with optically thin approximation. Is there any limitation within RadLib of using PM
    only with optically thin approximation?

    **This is an error; the reference to the optically thin approximation has been removed. It is true that the PM model can 
be used with any RTE solver. There is no limitation within RadLib that prevents its use with other RTE solvers.**
</font>
