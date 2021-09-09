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
   range of pressures under which the RCSLW model can be applied. A table summarizing these conditions has been added to
   the beginning of Section 2.**

2) Please rephrase and, if possible, simplify the sentence on lines 82-86 ("Radiation property models, including those
   implemented in RadLib, are typically developed using ... correlations and modeling assumptions [4].") It is difficult
   to understand what exactly the authors are trying to convey in this sentence.

   **Sentence has been revised for clarity.**

3) Line 92 - 95: "Modern band models .. cant lose accuracy when applied to nonhomogeneous media and may still require
   large numbers of RTE evaluations [1]." Should this be "<can> lose accuracy when applied …"?

   **Yes, it should. Typo has been fixed.**

4) In Figure 2, Example S5: Do "n=2" "n=4", etc mean the number of bands in RCSLW? It needs to be clarified.
   Furthermore, can the authors comment on the physical significance of RCSLW n =1 and how is this different from PM
   which uses a spectral average value?

   **The figure's caption has been updated to clarify this. The main difference between the PM model and RCSLW (or WSGG) with n=1 
is that the RCSLW model always considers one transparent gas (representing gaps in the absorption spectrum) in addition 
to some number of gray gases, whereas the PM model uses an average over the entire spectrum, gaps included. The "clear gas" 
concept is discussed on page 4 during the derivation of the gray gas spectral RTE (Eq. 5), but the PM model description 
did not indicate its deviation from this and has been revised to clarify that it does not consider a transparent gas in 
addition to its single gray gas.**

5) In Figure 2: This is a kind of cosmetic request, but still if the legends and symbols can be made consistent it will
   be easier to read.

6) In lines 499-501: Please clarify the sentence, "The PM absorption coefficient is 27.4 atm−1 m−1 , which results in a
   calculated optical thicknesses of 0.09 and 0.36 m in the thick and thin layers, respectively." Optical thickness is a
   dimensionless quantity, it cannot be 0.36 m. The thicknesses of layers are changing in S2, so what do these 0.09 and
   0.36 refer to?

   **Those numbers are intended to be optical thicknesses and should not have units. This has been fixed. The layer thicknesses in 
Example S2 are physical lengths, as indicated.**

7) In Section 5.1, please clarify which files and functions belong to FDS and which to RadLib. For example, in line
   544, "This was done by editing the radi.f90 file." By looking at the f90 extension the readers can guess that
   radi.f90 is part of FDS and not RadLib. But then in the next sentence, there are references to A_WSGG and KAPPA_WSGG
   functions. Are these part of FDS?

   **Sentence has been revised to clarify which files and functions belong to FDS.**

8) In lines 562-564: "The FDS default model uses a single gray gas with a composition and temperature dependent
   absorption coefficient computed from RADCAL." Is this equivalent to the PM model in RadLib? If so, a comparison with
   PM from RadLib and FDS default will be a good validation. Also, what RTE solver does FDS default use?

   **No, they are not equivalent. FDS uses a finite-volume discrete ordinates RTE solver, as specified in the first paragraph of Section 5.1.**

9) In Section 5.2 can the author comment on the computational cost of RadLib-coupled FDS runs? Some quantitative
   information on the computational cost of using RadLib for a coupled run will be very useful. For example, the authors
   can compare the cost of the same FDS configuration simulated without any radiation, with RadLib, and with the
   FDS-default model.

10) Line 624: "At present, it includes three major radiation property models - Planck Mean (PM) absorption coefficients
    using the optically thin approximation, the weighted sum of gray gases (WSGG) model,..." PM can be used with any RTE
    solver in principle, not just with optically thin approximation. Is there any limitation within RadLib of using PM
    only with optically thin approximation?

   **This is an error; the reference to the optically thin approximation has been removed. It is true that the PM model can 
be used with any RTE solver. There is no limitation within RadLib that prevents its use with other RTE solvers.**