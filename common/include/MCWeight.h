#pragma once

#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/JetIds.h"
#include "UHH2/common/include/BTagCalibrationStandalone.h"
#include "UHH2/common/include/Utils.h"

#include "TH2.h"

/** \brief Set the event weight according to the sample lumi and a target lumi
 *
 * This module only has an effect if "use_sframe_weight" is set to "false" to avoid
 * applying the same weight twice. Also, it will only run, if "dataset_type"
 * equals "MC".
 *
 * Interprets the following settings from the passed Context:
 *  - "dataset_lumi": the lumi of the current dataset, in inverse pb
 *  - "target_lumi": the data lumi to reweight to, in inverse pb
 * These are set automatically if running via SFrame by AnalysisModuleRunner.
 *
 * The event weight is multiplied with the ratio of dataset_lumi and target_lumi, independent
 * of the maximum number of processed events. This is different from sframe which
 * takes into account the number of events to process.
 */
class MCLumiWeight: public uhh2::AnalysisModule {
public:
    explicit MCLumiWeight(uhh2::Context & ctx);

    virtual bool process(uhh2::Event & event) override;

private:
    double factor = 1.0;
    bool use_sframe_weight;
};


/** \brief Reweight MC based on simulated and actual pileup
 *
 * Interprets "pileup_directory" and "pileup_directory_data" from Context, which should
 * be set to the path to root files which contain the pileup information for each MC
 * sample and data. If an empty value is given, no pileup reweighting is done.
 * "pileup_directory_data_up" and "pileup_directory_data_down" may be set as well.
 *
 * If sysType is set to "up" or "down", both path are needed: pileup_directory_data_<up/down>
 */
class MCPileupReweight: public uhh2::AnalysisModule {
public:
    explicit MCPileupReweight(uhh2::Context & ctx, const std::string & sysType="central");

    virtual bool process(uhh2::Event & event) override;

private:
   uhh2::Event::Handle<float> h_pu_weight_;
   uhh2::Event::Handle<float> h_pu_weight_up_;
   uhh2::Event::Handle<float> h_pu_weight_down_;
   TH1F * h_npu_mc;
   TH1F * h_npu_data;
   TH1F * h_npu_data_up;
   TH1F * h_npu_data_down;
   std::string sysType_;
};


/** \brief Vary renormalization and factorization scale up or down by factor 2
 *
 * Interprets "ScaleVariationMuR" and "ScaleVariationMuF" from Context, the values may be "up" or "down".
 * Any other value will result in no scale variation. This method also will have no effect on samples
 * where genInfo.systweight is not filled.
 */
class MCScaleVariation: public uhh2::AnalysisModule {
 public:
  explicit MCScaleVariation(uhh2::Context & ctx);

  virtual bool process(uhh2::Event & event) override;

  private:
  double syst_weight;
  int i_mu_r = 0, i_mu_f = 0;
  uhh2::Event::Handle<float> h_murmuf_weight_upup_;
  uhh2::Event::Handle<float> h_murmuf_weight_upnone_;
  uhh2::Event::Handle<float> h_murmuf_weight_noneup_;
  uhh2::Event::Handle<float> h_murmuf_weight_downdown_;
  uhh2::Event::Handle<float> h_murmuf_weight_downnone_;
  uhh2::Event::Handle<float> h_murmuf_weight_nonedown_;
};



/** \brief Apply muon scale factors
 *
 * https://twiki.cern.ch/twiki/bin/viewauth/CMS/MuonReferenceEffsRun2#Results_for_2015_data
 *
 * - only for applying pt- _and_ eta-scale dependent scale factors
 *
 * - parameters:
 *   - sf_file_path: path the root file with the scale factors
 *   - sf_name: directory name in the root file
 *   - sys_error_percantage: e.g. "1." for 1% of systematic error
 *   - weight_postfix: handle name for weights, e.g. "trigger" will produce the
 *     handles "weight_sfmu_trigger", "weight_sfmu_trigger_up" and
 *     "weight_sfmu_trigger_down"
 *   - sys_uncert: which uncertainty is applied to event.weight, can be "up",
 *     "down" or "nominal".
 *   - muons_handle_name: handle to the muon collection (the default points to
 *     event.muons)
 *   - absolute_eta: should be true if the eta range in the scale factor histogram is positive only
 *     (i.e. only shows absolute eta values); should be false if eta can also be negative (i.e. scale
 *     factors are not strictly symmetric around zero)
 */
class MCMuonScaleFactor: public uhh2::AnalysisModule {
public:
  explicit MCMuonScaleFactor(
    uhh2::Context & ctx,
    const std::string & sf_file_path,
    const std::string & sf_name,
    float sys_error_percantage,
    const std::string & weight_postfix="",
    bool etaYaxis=false,
    const std::string & sys_uncert="nominal",
    const std::string & muons_handle_name="muons",
    const bool absolute_eta = true
  );

  virtual bool process(uhh2::Event & event) override;
  virtual bool process_onemuon(uhh2::Event & event, int i);

private:
  uhh2::Event::Handle<std::vector<Muon>> h_muons_;
  std::unique_ptr<TH2> sf_hist_;
  uhh2::Event::Handle<float> h_muon_weight_;
  uhh2::Event::Handle<float> h_muon_weight_up_;
  uhh2::Event::Handle<float> h_muon_weight_down_;
  float sys_error_factor_;
  float eta_min_, eta_max_, pt_min_, pt_max_;
  int sys_direction_;
  bool etaYaxis_;
  const bool fAbsoluteEta;
};

// Muon tracking efficiency
// https://twiki.cern.ch/twiki/bin/view/CMS/MuonReferenceEffsRun2
class MCMuonTrkScaleFactor: public uhh2::AnalysisModule {
public:
  explicit MCMuonTrkScaleFactor(
    uhh2::Context & ctx,
    const std::string & sf_file_path,
    float sys_error_percantage,
    const std::string & weight_postfix="",
    const std::string & sys_uncert="nominal",
    const std::string & muons_handle_name="muons"
  );

  virtual bool process(uhh2::Event & event) override;

private:
  uhh2::Event::Handle<std::vector<Muon>> h_muons_;
  //  std::unique_ptr<TH2> sf_hist_;
  std::vector<float> eta_;
  std::vector<float> SFs_;
  std::vector<float> SFs_err_dn_;
  std::vector<float> SFs_err_up_;
  uhh2::Event::Handle<float> h_muontrk_weight_;
  uhh2::Event::Handle<float> h_muontrk_weight_up_;
  uhh2::Event::Handle<float> h_muontrk_weight_down_;
  float sys_error_factor_;
  float eta_min_, eta_max_;
  int sys_direction_;
};



/** \brief Apply electron scale factors
 *
 * https://twiki.cern.ch/twiki/bin/view/CMS/EgammaIDRecipesRun2
 *
 * - only for applying pt- _and_ eta-scale dependent scale factors
 *
 * - parameters:
 *   - sf_file_path: path the root file with the scale factors
 *   - sys_error_percantage: e.g. "1." for 1% of systematic error
 *   - weight_postfix: handle name for weights, e.g. "trigger" will produce the
 *     handles "weight_sfel_trigger", "weight_sfel_trigger_up" and
 *     "weight_sfel_trigger_down"
 *   - sys_uncert: which uncertainty is applied to event.weight, can be "up",
 *     "down" or "nominal".
 *   - electrons_handle_name: handle to the electrons collection (the default points to
 *     event.electrons)
 *   - absolute_eta: should be true if the eta range in the scale factor histogram is positive only
 *     (i.e. only shows absolute eta values); should be false if eta can also be negative (i.e. scale
 *     factors are not strictly symmetric around zero)
 */
class MCElecScaleFactor: public uhh2::AnalysisModule {
public:
  explicit MCElecScaleFactor(
    uhh2::Context & ctx,
    const std::string & sf_file_path,
    float sys_error_percantage,
    const std::string & weight_postfix="",
    const std::string & sys_uncert="nominal",
    const std::string & elecs_handle_name="electrons",
    const std::string & sf_name="EGamma_SF2D",
    const bool absolute_eta = true
  );

  virtual bool process(uhh2::Event & event) override;

private:
  uhh2::Event::Handle<std::vector<Electron>> h_elecs_;
  std::unique_ptr<TH2> sf_hist_;
  uhh2::Event::Handle<float> h_elec_weight_;
  uhh2::Event::Handle<float> h_elec_weight_up_;
  uhh2::Event::Handle<float> h_elec_weight_down_;
  float sys_error_factor_;
  float eta_min_, eta_max_, pt_min_, pt_max_;
  int sys_direction_;
  const bool fAbsoluteEta;
};


class BTagCalibrationReader;  // forward declaration
/** \brief apply btag scale factors
 *
 * jets_handle_name should point to a handle of type vector<Jet> _or_
 * vector<TopJet>, were in the latter case all of the subjets are used.
 *
 * measurementType and sysType are interpreted by the BTagCalibration
 * (check https://twiki.cern.ch/twiki/bin/viewauth/CMS/BTagCalibration).
 * Currently, sysType can be one of central, up, down, up_bc, down_bc, up_udsg,
 * down_udsg.
 *
 * This module is designed to be used with the CSVBTag class
 * (see include/JetIds.h) and only one operating point!
 *
 * These values are taken from the context:
 *  - "MCBtagEfficiencies" should be a path-string pointing to a file with three
 *    histograms, that were made with the main selection of your analysis
 *    applied (TH2, x->pt, y->eta):
 *    - BTagMCEffFlavBEff
 *    - BTagMCEffFlavCEff
 *    - BTagMCEffFlavUDSGEff
 *  - "BTagCalibration" should be a path-string pointing to the .csv file
 *    containing scale factors.
 */
class MCBTagScaleFactor: public uhh2::AnalysisModule {
public:
  explicit MCBTagScaleFactor(
    uhh2::Context & ctx,
    BTag::algo tagger,
    BTag::wp wp,
    const std::string & jets_handle_name="jets",
    const std::string & sysType="central",
    const std::string & measType_bc="mujets",
    const std::string & measType_udsg="incl",
    const std::string & xml_param_name="MCBtagEfficiencies",
    const std::string & weights_name_postfix="",
    const std::string & xml_calib_name="BTagCalibration"
  );


  virtual bool process(uhh2::Event & event) override;

protected:
  std::tuple<float, float, float> get_weight_btag(const std::vector<TopJet> &jets,
                                                  uhh2::Event & event);
  std::pair<float, float> get_SF_btag(float pt, float abs_eta, int flav);

  BTag btag_;
  std::unique_ptr<BTagCalibrationReader> calib_up_;
  std::unique_ptr<BTagCalibrationReader> calib_;
  std::unique_ptr<BTagCalibrationReader> calib_down_;
  std::unique_ptr<TH2> eff_b_;
  std::unique_ptr<TH2> eff_c_;
  std::unique_ptr<TH2> eff_udsg_;
  uhh2::Event::Handle<std::vector<Jet>> h_jets_;
  uhh2::Event::Handle<std::vector<TopJet>> h_topjets_;
  std::string sysType_;
  uhh2::Event::Handle<float> h_btag_weight_;
  uhh2::Event::Handle<float> h_btag_weight_up_;
  uhh2::Event::Handle<float> h_btag_weight_down_;
  uhh2::Event::Handle<float> h_btag_weight_bc_up_;
  uhh2::Event::Handle<float> h_btag_weight_bc_down_;
  uhh2::Event::Handle<float> h_btag_weight_udsg_up_;
  uhh2::Event::Handle<float> h_btag_weight_udsg_down_;
};


/**\brief Apply reweighting of b-tag discriminant distribution
 *
 * jets_handle_name should point to a handle of type vector<Jet>
 *
 * Twiki: https://twiki.cern.ch/twiki/bin/view/CMS/BtagRecommendation (including information how to handle correlations between years!)
 *
 * For each jet, the event.weight will be modified by one factor. The factor depends on the jet pt, eta, hadronFlavor, and the b-tagging discriminant itself.
 * The variations work as follows:
 *
 * The weight used for "central" depends on whether JES is varied or not (defined by "jecsmear_direction" in your config XML):
 * If the nominal JES correction is used, the central weight is the one called "central" in the b-tagging SF file. If a JES variation is applied, the central
 * weight will the one called "up/down_jes" in the b-tagging SF file. I.e. the JES-related uncertainty of the b-tagging SFs must be 100% correlated with the
 * actual JES variation in your analysis. If you are interested in the split JES uncertainty sources, you can specify "jecsmear_source" in your XML config;
 * this defaults to "Total", so you don't have to do anything if you are only interested in the total JES variations. But if you set "jecsmear_source" to
 * e.g. "Fragmentation" while "jecsmear_direction" is not nominal, then your jet corretor module will apply only the up/down variation related to the
 * "Fragmentation" uncertainty source and this b-tagging SF module will apply the "up/down_jesFragmentation" SF (it will still be called "central" in the
 * AnalysisTree).
 *
 * The other variations not related to JES work as usual. Set "SystDirection_BTaggingShape" (default: "central") in your config XML to the corresponding
 * variation. Available options are called like the SysType enums (see below). Note that this needs to stay "central" if you are doing JES variations!
 */
class MCBTagDiscriminantReweighting: public uhh2::AnalysisModule {
public:
  explicit MCBTagDiscriminantReweighting(
    uhh2::Context & ctx,
    BTag::algo algorithm,
    const std::string & jets_handle_name="jets",
    const std::string & weights_name_postfix="",
    const std::string & measType="iterativefit"
  );

  virtual bool process(uhh2::Event & event) override;

private:
  enum class SysType {
    central,
    cferr1_up,
    cferr1_down,
    cferr2_up,
    cferr2_down,
    lf_up,
    lf_down,
    lfstats1_up,
    lfstats1_down,
    lfstats2_up,
    lfstats2_down,
    hf_up,
    hf_down,
    hfstats1_up,
    hfstats1_down,
    hfstats2_up,
    hfstats2_down,
  };

  const std::string fSystDirectionConfigName = "SystDirection_BTaggingShape";
  const BTag::algo fAlgorithm;
  const Year fYear;
  const uhh2::Event::Handle<std::vector<Jet>> h_jets;

  const uhh2::Event::Handle<float> h_weight_central;
  const uhh2::Event::Handle<float> h_weight_cferr1_up;
  const uhh2::Event::Handle<float> h_weight_cferr1_down;
  const uhh2::Event::Handle<float> h_weight_cferr2_up;
  const uhh2::Event::Handle<float> h_weight_cferr2_down;
  const uhh2::Event::Handle<float> h_weight_lf_up;
  const uhh2::Event::Handle<float> h_weight_lf_down;
  const uhh2::Event::Handle<float> h_weight_lfstats1_up;
  const uhh2::Event::Handle<float> h_weight_lfstats1_down;
  const uhh2::Event::Handle<float> h_weight_lfstats2_up;
  const uhh2::Event::Handle<float> h_weight_lfstats2_down;
  const uhh2::Event::Handle<float> h_weight_hf_up;
  const uhh2::Event::Handle<float> h_weight_hf_down;
  const uhh2::Event::Handle<float> h_weight_hfstats1_up;
  const uhh2::Event::Handle<float> h_weight_hfstats1_down;
  const uhh2::Event::Handle<float> h_weight_hfstats2_up;
  const uhh2::Event::Handle<float> h_weight_hfstats2_down;

  SysType fSysType;
  std::string fCentralOrJES;

  std::unique_ptr<BTagCalibrationReader> reader;
};


/** \brief Vary Tau efficiency
 *
 * https://twiki.cern.ch/twiki/bin/view/CMS/TauIDRecommendation13TeV#Tau_ID_efficiency
 *
 * Interprets "TauIdVariation" from Context, the values may be "up" or "down".
 * Any other value will result in no scale variation.
 */
class TauEffVariation: public uhh2::AnalysisModule {
public:
  explicit TauEffVariation(uhh2::Context & ctx);

  virtual bool process(uhh2::Event & event) override;

private:
  int i_TauEff = 0;
  // SF for Run-2 2016 is 0.83 while SF for Run-1 and Run-2 2015 is equal to 1.
  double SF_TauId = 0.9;
};


/** \brief Vary Tau charge
 *
 * https://twiki.cern.ch/twiki/bin/view/CMS/TauIDRecommendation13TeV#Tau_charge_misidentification_rat
 *
 * Interprets "TauChargeVariation" from Context, the values may be "up" or "down".
 * Any other value will result in no scale variation.
 */
class TauChargeVariation: public uhh2::AnalysisModule {
public:
  explicit TauChargeVariation(uhh2::Context & ctx);

  virtual bool process(uhh2::Event & event) override;

private:
  int i_TauCharge = 0;
};
