
#include "customized_constants.h"
#include "customized.h"
#include <iostream>
#include <iomanip>
#include <array>

int main()
{

    ofstream myfile_infections;
    ofstream myfile_infections_table;
    ofstream myfile_screening_table;

    ofstream myfile_compartments_per_day;
    ofstream customized_scenarios_filtered;
    ofstream best_scenarios_total_infections;
    ofstream best_scenarios_peak_infections;

    myfile_infections_table.open("table_measures.txt");
    myfile_screening_table.open("table_tests.txt");
    customized_scenarios_filtered.open("customized_generic.txt");
    best_scenarios_total_infections.open("best_scenarios_total_infections.txt");
    best_scenarios_peak_infections.open("best_scenarios_peak_infections.txt");


    //myfile_compartments.open("table_print_compartments_new.txt");
    //myfile_compartments_per_day.open("table_print_compartments_per_day_test_4.txt");


    //unsigned int vaccines_number_today;
    double counter_for_periods = 0;

    const int DAYS = 80;
    const int REPORTING_INTERVAL = 3; //every day and each interval is 8 hours (3 intervals/day)
    const int TOTAL_PERIODS_NUMBER = DAYS * REPORTING_INTERVAL; //number of periods/cycles we are running the simulation

    std::vector<region>	region_list;  // create your region_list

    region region1;
    region1.population_size = 24000; //fix num
    region1.ID = 1;
    region_list.push_back(region1);  // insert region1 to the region_list

    int disp_period_num = 0;   //counter, every 2 days
    unsigned int week_N_S = 1;     //counter for exogenous shock, X/week so X every 7 days (i.e. 7*3 cycles)
    unsigned int week_N_F = 1;
    unsigned int week_W_S = 1;
    unsigned int week_W_F = 1;
    unsigned int week_B_S = 1;
    unsigned int week_B_F = 1;

    //measures for plotting
    double number_of_infections_no_screening = 0.0;
    double peak_of_infections_no_screening = 0.0;
    double max_ratio_total_infections_no_screening_for_unvaccinated_students = 0.0;
    double max_ratio_peak_infections_no_screening_for_unvaccinated_students = 0.0;
    double max_ratio_total_infections_14d_for_unvaccinated_students = 0.0;
    double max_ratio_peak_infections_14d_for_unvaccinated_students = 0.0;
    double max_ratio_total_infections_7d_for_unvaccinated_students = 0.0;
    double max_ratio_peak_infections_7d_for_unvaccinated_students = 0.0;
    double max_ratio_total_infections_3d_for_unvaccinated_students = 0.0;
    double max_ratio_peak_infections_3d_for_unvaccinated_students = 0.0;
    double max_ratio_total_infections_2d_for_unvaccinated_students = 0.0;
    double max_ratio_peak_infections_2d_for_unvaccinated_students = 0.0;
    double max_ratio_total_infections_1d_for_unvaccinated_students = 0.0;
    double max_ratio_peak_infections_1d_for_unvaccinated_students = 0.0;

    double tau_array_for_max_ratio_total_infections_no_screening_for_unvaccinated_students[5] = { 0,0,0,0,0 }; //Tau_W_S, Tau_B_S, Tau_N_F, Tau_W_F, Tau_B_F
    double tau_array_for_max_ratio_peak_infections_no_screening_for_unvaccinated_students[5] = { 0,0,0,0,0 };
    double tau_array_for_max_ratio_total_infections_14d_for_unvaccinated_students[5] = { 0,0,0,0,0 };
    double tau_array_for_max_ratio_peak_infections_14d_for_unvaccinated_students[5] = { 0,0,0,0,0 };
    double tau_array_for_max_ratio_total_infections_7d_for_unvaccinated_students[5] = { 0,0,0,0,0 };
    double tau_array_for_max_ratio_peak_infections_7d_for_unvaccinated_students[5] = { 0,0,0,0,0 };
    double tau_array_for_max_ratio_total_infections_3d_for_unvaccinated_students[5] = { 0,0,0,0,0 };
    double tau_array_for_max_ratio_peak_infections_3d_for_unvaccinated_students[5] = { 0,0,0,0,0 };
    double tau_array_for_max_ratio_total_infections_2d_for_unvaccinated_students[5] = { 0,0,0,0,0 };
    double tau_array_for_max_ratio_peak_infections_2d_for_unvaccinated_students[5] = { 0,0,0,0,0 };
    double tau_array_for_max_ratio_total_infections_1d_for_unvaccinated_students[5] = { 0,0,0,0,0 };
    double tau_array_for_max_ratio_peak_infections_1d_for_unvaccinated_students[5] = { 0,0,0,0,0 };


    double N_U_t;
    double GAMMA; //mask
    double LAMBDA; //rate of becoming eligible
    double OMEGA;
    double EPSILON_W;  // vaccine effectiveness against infection
    double EPSILON_B;
    double UPSILON_W; // vaccine effectiveness against hospitalization
    double UPSILON_B;

    double BETA_NS_NS_t;
    double BETA_NF_NS_t;
    double BETA_WS_NS_t;
    double BETA_WF_NS_t;
    double BETA_BS_NS_t;
    double BETA_BF_NS_t;

    double BETA_NS_NF_t;
    double BETA_NF_NF_t;
    double BETA_WS_NF_t;
    double BETA_WF_NF_t;
    double BETA_BS_NF_t;
    double BETA_BF_NF_t;

    double BETA_NS_WS_t;
    double BETA_NF_WS_t;
    double BETA_WS_WS_t;
    double BETA_WF_WS_t;
    double BETA_BS_WS_t;
    double BETA_BF_WS_t;

    double BETA_NS_WF_t;
    double BETA_NF_WF_t;
    double BETA_WS_WF_t;
    double BETA_WF_WF_t;
    double BETA_BS_WF_t;
    double BETA_BF_WF_t;

    double BETA_NS_BS_t;
    double BETA_NF_BS_t;
    double BETA_WS_BS_t;
    double BETA_WF_BS_t;
    double BETA_BS_BS_t;
    double BETA_BF_BS_t;

    double BETA_NS_BF_t;
    double BETA_NF_BF_t;
    double BETA_WS_BF_t;
    double BETA_WF_BF_t;
    double BETA_BS_BF_t;
    double BETA_BF_BF_t;

    double R_NS_NS_t;
    double R_NF_NS_t;
    double R_WS_NS_t;
    double R_WF_NS_t;
    double R_BS_NS_t;
    double R_BF_NS_t;

    double R_NS_NF_t;
    double R_NF_NF_t;
    double R_WS_NF_t;
    double R_WF_NF_t;
    double R_BS_NF_t;
    double R_BF_NF_t;

    double R_NS_WS_t;
    double R_NF_WS_t;
    double R_WS_WS_t;
    double R_WF_WS_t;
    double R_BS_WS_t;
    double R_BF_WS_t;

    double R_NS_WF_t;
    double R_NF_WF_t;
    double R_WS_WF_t;
    double R_WF_WF_t;
    double R_BS_WF_t;
    double R_BF_WF_t;

    double R_NS_BS_t;
    double R_NF_BS_t;
    double R_WS_BS_t;
    double R_WF_BS_t;
    double R_BS_BS_t;
    double R_BF_BS_t;

    double R_NS_BF_t;
    double R_NF_BF_t;
    double R_WS_BF_t;
    double R_WF_BF_t;
    double R_BS_BF_t;
    double R_BF_BF_t;

    double DELTA_N_S;
    double DELTA_N_F;
    double DELTA_W_S;
    double DELTA_W_F;
    double DELTA_B_S;
    double DELTA_B_F;

    double PI_N_S;
    double PI_N_F;
    double PI_W_S;
    double PI_W_F;
    double PI_B_S;
    double PI_B_F;

    double R_0_N_S;
    double R_0_N_F;
    double R_0_W_S;
    double R_0_W_F;
    double R_0_B_S;
    double R_0_B_F;

    double TAU_N_S;
    double TAU_W_S;
    double TAU_B_S;
    double TAU_N_F;
    double TAU_W_F;
    double TAU_B_F;

    //double TAU_N_S_new;
    //double TAU_W_S_new;
    //double TAU_B_S_new;

    double ETA; //screening compliance rate
    double U_N_S_0;
    double U_N_F_0;
    double U_W_S_0;
    double U_W_F_0;
    double U_B_S_0;
    double U_B_F_0;

    double initial_asymptomatic_N_S = 45; // 45;
    double initial_asymptomatic_N_F = 3; // 3;
    double initial_asymptomatic_W_S = 45;
    double initial_asymptomatic_W_F = 3;
    double initial_asymptomatic_B_S = 45; // 45;
    double initial_asymptomatic_B_F = 3; // 3;

    //Screening arrays:
    double TAU_N_S_array[] = { 0, 1.0 / (3 * 14.0), 1.0 / (3 * 7.0), 1.0 / (3 * 3.0), 1.0 / (3 * 2.0), 1.0 / (3 * 1.0) };
    double TAU_W_S_array[] = { 0, 1.0 / (3 * 14.0), 1.0 / (3 * 7.0), 1.0 / (3 * 3.0), 1.0 / (3 * 2.0), 1.0 / (3 * 1.0) };
    double TAU_B_S_array[] = { 0, 1.0 / (3 * 14.0), 1.0 / (3 * 7.0), 1.0 / (3 * 3.0), 1.0 / (3 * 2.0), 1.0 / (3 * 1.0) };
    double TAU_N_F_array[] = { 0, 1.0 / (3 * 14.0), 1.0 / (3 * 7.0), 1.0 / (3 * 3.0), 1.0 / (3 * 2.0), 1.0 / (3 * 1.0) };
    double TAU_W_F_array[] = { 0, 1.0 / (3 * 14.0), 1.0 / (3 * 7.0), 1.0 / (3 * 3.0), 1.0 / (3 * 2.0), 1.0 / (3 * 1.0) };
    double TAU_B_F_array[] = { 0, 1.0 / (3 * 14.0), 1.0 / (3 * 7.0), 1.0 / (3 * 3.0), 1.0 / (3 * 2.0), 1.0 / (3 * 1.0) };

    
    double LAMBDA_array[] = { 0 };// { 0, 1.0 / (3 * 6.0 * 7) };// { 0, 1.0 / (3 * 5.0 * 7), 1.0 / (3 * 6.0 * 7), 1.0 / (3 * 7.0 * 7) };

    double initial_U_N_S_array[] = { 4000 }; 
    double initial_U_N_F_array[] = { 267 }; 
    double initial_U_W_S_array[] = { 4000 };// { 4000, 10000 };
    double initial_U_W_F_array[] = { 267 }; // { 267, 667};


    //For sensitivity analysis:
    double ETA_array[] = { 0.75 }; // { 0.75, 0.9}; // { 0.5, 0.75, 0.9, 0.95, 1 };    //compliance to screening
    double GAMMA_array[] = { 0.5 }; // { 0.5, 0.75, 0.95 };    //mask
    double OMEGA_array[] = { 0.5}; // either {0.5} or {0.95}   //proportion of omicron
    double R0_S_Delta_array[] = { 6 }; // (array of size 1) Base case: 6, Best case: 5, Worst case: 7 //basic reproduction number input: delta variant, students
    double R0_F_Delta_array[] = { 3.2 }; // (array of size 1) Base case: 3.2, Best case: 2.2, Worst case: 4.2 //basic reproduction number input: delta variant, faculty
    double R0_S_Delta = R0_S_Delta_array[0];
    double R0_F_Delta = R0_F_Delta_array[0];

    //Size of arrays:
    int TAU_N_S_array_size = sizeof(TAU_N_S_array) / sizeof(TAU_N_S_array[0]);
    int TAU_W_S_array_size = sizeof(TAU_W_S_array) / sizeof(TAU_W_S_array[0]);
    int TAU_B_S_array_size = sizeof(TAU_B_S_array) / sizeof(TAU_B_S_array[0]);
    int TAU_N_F_array_size = sizeof(TAU_N_F_array) / sizeof(TAU_N_F_array[0]);
    int TAU_W_F_array_size = sizeof(TAU_W_F_array) / sizeof(TAU_W_F_array[0]);
    int TAU_B_F_array_size = sizeof(TAU_B_F_array) / sizeof(TAU_B_F_array[0]);
    int initial_U_N_S_array_size = sizeof(initial_U_N_S_array) / sizeof(initial_U_N_S_array[0]);
    int initial_U_N_F_array_size = sizeof(initial_U_N_F_array) / sizeof(initial_U_N_F_array[0]);
    int initial_U_W_S_array_size = sizeof(initial_U_W_S_array) / sizeof(initial_U_W_S_array[0]);
    int initial_U_W_F_array_size = sizeof(initial_U_W_F_array) / sizeof(initial_U_W_F_array[0]);
    int ETA_array_size = sizeof(ETA_array) / sizeof(ETA_array[0]);
    int GAMMA_array_size = sizeof(GAMMA_array) / sizeof(GAMMA_array[0]);
    int LAMBDA_array_size = sizeof(LAMBDA_array) / sizeof(LAMBDA_array[0]);
    int OMEGA_array_size = sizeof(OMEGA_array) / sizeof(OMEGA_array[0]);
    

    myfile_infections_table << "% Omicron \t" << "U_N,F(0) \t" << "U_N,S(0) \t" << "U_W,F(0) \t" << "U_W,S(0) \t" << "U_B,F(0) \t" << "U_B,S(0) \t" << " Scr compl (eta) \t" << "Mask reduction rate (gamma) \t" << "weeks until eligible \t" << "Tau_N_S \t" << "Tau_W_S \t" << "Tau_B_S \t" << "Tau_N_F \t" << "Tau_W_F \t" << "Tau_B_F \t";
    myfile_infections_table << "# inf. N,S \t" << "# inf. N,F \t" << "# inf. No immunity \t" << "# inf. W,S \t" << "# inf. W,F \t" << "# inf. Waning immunity \t" << "# inf. B,S \t" << "# inf. B,F \t" << "# inf. boosted immunity \t" << "# inf. combined \t";
    myfile_infections_table << "# Hosp. N,S \t" << "# Hosp. N,F \t" << "# Hosp. No immunity \t" << "# Hosp. W,S \t" << "# Hosp. W,F \t" << "# Hosp. Waning immunity \t" << "# Hosp. B,S \t" << "# Hosp. B,F \t" << "# Hosp. Boosted immunity \t" << "# Hosp. combined \t";
    myfile_infections_table << "# deaths N,S \t" << "# deaths  N,F \t" << "# deaths  No immunity \t" << "# deaths W,S \t" << "# deaths  W,F \t" << "# deaths  Waning immunity \t" << "# deaths B,S \t" << "# deaths  B,F \t" << "# deaths  Boosted immunity \t" << "# deaths  combined \t";
    myfile_infections_table << "Peak # Inf No immunity \t" << "Peak Day Inf No immunity \t" << "Peak # Hosp No immunity \t" << "Peak Day Hosp No immunity \t";
    myfile_infections_table << "Peak # Inf Waning immunity \t" << "Peak Day Inf Waning immunity \t" << "Peak # Hosp Waning immunity \t" << "Peak Day Hosp Waning immunity \t";
    myfile_infections_table << "Peak # Inf Boosted immunity \t" << "Peak Day Inf Boosted immunity \t" << "Peak # Hosp Boosted immunity \t" << "Peak Day Hosp Boosted immunity \t";
    myfile_infections_table << "Peak # Inf combined \t" << "Peak Day Inf combined \t" << "Peak # Hosp combined \t" << "Peak Day Hosp combined \t" << endl;

    myfile_screening_table << "% Omicron \t" << "U_N,F(0) \t" << "U_N,S(0) \t" << "U_W,F(0) \t" << "U_W,S(0) \t" << "U_B,F(0) \t" << "U_B,S(0) \t" << " Scr compl (eta) \t" << "Mask reduction rate (gamma) \t" << "weeks until eligible \t" << "Tau_N_S \t" << "Tau_W_S \t" << "Tau_B_S \t" << "Tau_N_F \t" << "Tau_W_F \t" << "Tau_B_F \t";
    myfile_screening_table << "Tests_N_S /day\t" << "Tests_N_F /day \t" << "Tests_no_immunity /day\t" << "Tests_W_S /day \t" << "Tests_W_F /day \t" << "Tests_waning_immunity /day \t" << "Tests_B_S  /day\t" << "Tests_B_F /day \t" << "Tests_boosted_immunity /day \t" << "Tests_combined /day \t" << endl;

    customized_scenarios_filtered << "% Omicron \t" << "U_N,F(0) \t" << "U_N,S(0) \t" << "U_W,F(0) \t" << "U_W,S(0) \t" << "U_B,F(0) \t" << "U_B,S(0) \t" << " Scr compl (eta) \t" << "Mask reduction rate (gamma) \t" << "weeks until eligible \t";
    customized_scenarios_filtered << "Tau_N_S \t" << "Tau_W_S \t" << "Tau_B_S \t" << "Tau_N_F \t" << "Tau_W_F \t" << "Tau_B_F \t";
    //customized_scenarios_filtered <<  "# inf. combined \t"<<"Peak # inf. combined \t" << "Tests_combined /day \t" <<"Ratio total infections per 100 tests \t" << "Ratio peak infections per 100 tests \t"<< endl;
    customized_scenarios_filtered << "Ratio total infections per 100 tests \t" << "Ratio peak infections per 100 tests \t" << endl;


    best_scenarios_total_infections << "% Omicron \t" << "U_N,F(0) \t" << "U_N,S(0) \t" << "U_W,F(0) \t" << "U_W,S(0) \t" << "U_B,F(0) \t" << "U_B,S(0) \t" << " Scr compl (eta) \t" << "Mask reduction rate (gamma) \t" << "weeks until eligible \t";
    best_scenarios_total_infections << "Tau_N_S \t" << "Tau_W_S \t" << "Tau_B_S \t" << "Tau_N_F \t" << "Tau_W_F \t" << "Tau_B_F \t";
    best_scenarios_total_infections << "Ratio of total infections averted per 100 tests \t" << endl;

    best_scenarios_peak_infections << "% Omicron \t" << "U_N,F(0) \t" << "U_N,S(0) \t" << "U_W,F(0) \t" << "U_W,S(0) \t" << "U_B,F(0) \t" << "U_B,S(0) \t" << " Scr compl (eta) \t" << "Mask reduction rate (gamma) \t" << "weeks until eligible \t";
    best_scenarios_peak_infections << "Tau_N_S \t" << "Tau_W_S \t" << "Tau_B_S \t" << "Tau_N_F \t" << "Tau_W_F \t" << "Tau_B_F \t";
    best_scenarios_peak_infections << "Ratio of peak infections averted per 100 tests \t" << endl;


    for (int o = 0; o < OMEGA_array_size; o++)
    {
        for (int n = 0; n < initial_U_W_S_array_size; n++)
        {

            for (int k = 0; k < initial_U_N_S_array_size; k++)
            {
                for (int e = 0; e < ETA_array_size; e++)
                {
                    for (int a = 0; a < GAMMA_array_size; a++)
                    {
                        for (int p = 0; p < LAMBDA_array_size; p++)
                        {
                            for (int q = 0; q < TAU_N_S_array_size; q++)
                            {
                                for (int w = 0; (w < TAU_W_S_array_size) && (w <= q); w++)
                                {
                                    for (int b = 0; (b < TAU_B_S_array_size) && (b <= w); b++)
                                    {
                                       // for (int q_f = 0; q_f < TAU_N_F_array_size; q_f++)
                                       // {
                                         //  for (int w_f = 0; (w_f < TAU_W_F_array_size) && (w_f <= q_f); w_f++)
                                         //   {
                                             //  for (int b_f = 0; (b_f < TAU_B_F_array_size) && (b_f <= w_f); b_f++)
                                              //  {

                                                    TAU_N_S = TAU_N_S_array[q];
                                                    TAU_W_S = TAU_W_S_array[w];//
                                                    TAU_B_S = TAU_B_S_array[b];//

                                                    TAU_N_F = TAU_N_S;
                                                    TAU_W_F = TAU_W_S;
                                                    TAU_B_F = TAU_B_S;

                                                   //uncomment if we differentiate between faculty and students
                                                  //  TAU_N_F = TAU_N_F_array[q_f];
                                                  //  TAU_W_F = TAU_W_F_array[w_f];//
                                                   // TAU_B_F = TAU_B_F_array[b_f];//

                                                    U_N_S_0 = initial_U_N_S_array[k];
                                                    U_N_F_0 = initial_U_N_F_array[k];
                                                    U_W_S_0 = initial_U_W_S_array[n];
                                                    U_W_F_0 = initial_U_W_F_array[n];
                                                    U_B_S_0 = 22500 - U_N_S_0 - U_W_S_0;
                                                    U_B_F_0 = 1500 - U_N_F_0 - U_W_F_0;


                                                    ETA = ETA_array[e];
                                                    GAMMA = GAMMA_array[a];
                                                    LAMBDA = LAMBDA_array[p];
                                                    OMEGA = OMEGA_array[o];


                                                    counter_for_periods = 0;
                                                    disp_period_num = 0;
                                                    week_N_S = 1;
                                                    week_N_F = 1;
                                                    week_W_S = 1;
                                                    week_W_F = 1;
                                                    week_B_S = 1;
                                                    week_B_F = 1;



                                                    int loop_index;
                                                    loop_index = TOTAL_PERIODS_NUMBER;
                                                    for (int i = 0; i < loop_index; i++)
                                                    {


                                                        for (std::vector<region>::iterator it = region_list.begin(); it != region_list.end(); ++it)
                                                        {   //"it" is now a pointer pointing to each region, so not only "it" shows the information on each region
                                                        //but also if we change something in "it", the region in the region_list will change


                                                            if (i == 0) //Initializations
                                                            {
                                                                if (it->ID == 1)
                                                                {
                                                                    it->dead_S = 0.0;
                                                                    it->dead_F = 0.0;

                                                                    it->current_asymptomatic_N_S = initial_asymptomatic_N_S;          //A(1)
                                                                    it->asymptomatic_infected_N_S = it->current_asymptomatic_N_S;
                                                                    it->previous_uninfected_N_S = U_N_S_0;         //U(0) //INSERT HERE
                                                                    it->current_uninfected_N_S = U_N_S_0 - it->current_asymptomatic_N_S;     //U(1) //INSERT 
                                                                    it->uninfected_N_S = it->current_uninfected_N_S;
                                                                    it->previous_asymptomatic_infected_N_S = 0.0;  //A(0)
                                                                    it->recovered_unknown_N_S = 0.0; //INSERT HERE
                                                                    it->recovered_known_N_S = 0.0;        //INSERT HERE
                                                                    it->hospitalized_N_S = 0.0;
                                                                    it->current_exposed_asymptomatic_N_S = 0.0;
                                                                    it->current_hospitalized_N_S = 0.0;
                                                                    it->current_TP_N_S = 0.0;
                                                                    it->current_symptomatic_N_S = 0.0;
                                                                    it->exposed_asymptomatic_N_S = it->current_exposed_asymptomatic_N_S;
                                                                    it->false_positive_N_S = 0.0;
                                                                    it->false_positive_RU_N_S = 0.0;
                                                                    it->true_positive_N_S = 0.0;
                                                                    it->symptomatic_infected_N_S = 0.0;


                                                                    it->current_asymptomatic_N_F = initial_asymptomatic_N_F;          //A(1)
                                                                    it->asymptomatic_infected_N_F = it->current_asymptomatic_N_F;
                                                                    it->previous_uninfected_N_F = U_N_F_0;         //U(0) //INSERT HERE
                                                                    it->current_uninfected_N_F = U_N_F_0 - it->current_asymptomatic_N_F;   //U(1) //INSERT HERE
                                                                    it->uninfected_N_F = it->current_uninfected_N_F;
                                                                    it->previous_asymptomatic_infected_N_F = 0.0;  //A(0)
                                                                    it->recovered_unknown_N_F = 0.0; //INSERT HERE
                                                                    it->recovered_known_N_F = 0.0;        //INSERT HERE
                                                                    it->hospitalized_N_F = 0.0;
                                                                    it->current_exposed_asymptomatic_N_F = 0.0;
                                                                    it->current_hospitalized_N_F = 0.0;
                                                                    it->current_TP_N_F = 0.0;
                                                                    it->current_symptomatic_N_F = 0.0;
                                                                    it->exposed_asymptomatic_N_F = it->current_exposed_asymptomatic_N_F;
                                                                    it->false_positive_N_F = 0.0;
                                                                    it->false_positive_RU_N_F = 0.0;
                                                                    it->true_positive_N_F = 0.0;
                                                                    it->symptomatic_infected_N_F = 0.0;

                                                                    it->current_asymptomatic_W_S = initial_asymptomatic_W_S;          //A(1)
                                                                    it->asymptomatic_infected_W_S = it->current_asymptomatic_W_S;
                                                                    it->previous_uninfected_W_S = U_W_S_0;         //U(0) //INSERT HERE
                                                                    it->current_uninfected_W_S = U_W_S_0 - it->current_asymptomatic_W_S;     //U(1) //INSERT 
                                                                    it->uninfected_W_S = it->current_uninfected_W_S;
                                                                    it->previous_asymptomatic_infected_W_S = 0.0;  //A(0)
                                                                    it->recovered_unknown_W_S = 0.0; //INSERT HERE
                                                                    it->recovered_known_W_S = 0.0;        //INSERT HERE
                                                                    it->hospitalized_W_S = 0.0;
                                                                    it->current_exposed_asymptomatic_W_S = 0.0;
                                                                    it->current_hospitalized_W_S = 0.0;
                                                                    it->current_TP_W_S = 0.0;
                                                                    it->current_symptomatic_W_S = 0.0;
                                                                    it->exposed_asymptomatic_W_S = it->current_exposed_asymptomatic_W_S;
                                                                    it->false_positive_W_S = 0.0;
                                                                    it->false_positive_RU_W_S = 0.0;
                                                                    it->true_positive_W_S = 0.0;
                                                                    it->symptomatic_infected_W_S = 0.0;


                                                                    it->current_asymptomatic_W_F = initial_asymptomatic_W_F;          //A(1)
                                                                    it->asymptomatic_infected_W_F = it->current_asymptomatic_W_F;
                                                                    it->previous_uninfected_W_F = U_W_F_0;         //U(0) //INSERT HERE
                                                                    it->current_uninfected_W_F = U_W_F_0 - it->current_asymptomatic_W_F;   //U(1) //INSERT HERE
                                                                    it->uninfected_W_F = it->current_uninfected_W_F;
                                                                    it->previous_asymptomatic_infected_W_F = 0.0;  //A(0)
                                                                    it->recovered_unknown_W_F = 0.0; //INSERT HERE
                                                                    it->recovered_known_W_F = 0.0;        //INSERT HERE
                                                                    it->hospitalized_W_F = 0.0;
                                                                    it->current_exposed_asymptomatic_W_F = 0.0;
                                                                    it->current_hospitalized_W_F = 0.0;
                                                                    it->current_TP_W_F = 0.0;
                                                                    it->current_symptomatic_W_F = 0.0;
                                                                    it->exposed_asymptomatic_W_F = it->current_exposed_asymptomatic_W_F;
                                                                    it->false_positive_W_F = 0.0;
                                                                    it->false_positive_RU_W_F = 0.0;
                                                                    it->true_positive_W_F = 0.0;
                                                                    it->symptomatic_infected_W_F = 0.0;

                                                                    it->current_asymptomatic_B_S = initial_asymptomatic_B_S;          //A(1)
                                                                    it->asymptomatic_infected_B_S = it->current_asymptomatic_B_S;
                                                                    it->previous_uninfected_B_S = U_B_S_0;         //U(0) //INSERT HERE
                                                                    it->current_uninfected_B_S = U_B_S_0 - it->current_asymptomatic_B_S;     //U(1) //INSERT 
                                                                    it->uninfected_B_S = it->current_uninfected_B_S;
                                                                    it->previous_asymptomatic_infected_B_S = 0.0;  //A(0)
                                                                    it->recovered_unknown_B_S = 0.0; //INSERT HERE
                                                                    it->recovered_known_B_S = 0.0;        //INSERT HERE
                                                                    it->hospitalized_B_S = 0.0;
                                                                    it->current_exposed_asymptomatic_B_S = 0.0;
                                                                    it->current_hospitalized_B_S = 0.0;
                                                                    it->current_TP_B_S = 0.0;
                                                                    it->current_symptomatic_B_S = 0.0;
                                                                    it->exposed_asymptomatic_B_S = it->current_exposed_asymptomatic_B_S;
                                                                    it->false_positive_B_S = 0.0;
                                                                    it->false_positive_RU_B_S = 0.0;
                                                                    it->true_positive_B_S = 0.0;
                                                                    it->symptomatic_infected_B_S = 0.0;


                                                                    it->current_asymptomatic_B_F = initial_asymptomatic_B_F;          //A(1)
                                                                    it->asymptomatic_infected_B_F = it->current_asymptomatic_B_F;
                                                                    it->previous_uninfected_B_F = U_B_F_0;         //U(0) //INSERT HERE
                                                                    it->current_uninfected_B_F = U_B_F_0 - it->current_asymptomatic_B_F;  //U(1) //INSERT HERE
                                                                    it->uninfected_B_F = it->current_uninfected_B_F;
                                                                    it->previous_asymptomatic_infected_B_F = 0.0;  //A(0)
                                                                    it->recovered_unknown_B_F = 0.0; //INSERT HERE
                                                                    it->recovered_known_B_F = 0.0;        //INSERT HERE
                                                                    it->hospitalized_B_F = 0.0;
                                                                    it->current_exposed_asymptomatic_B_F = 0.0;
                                                                    it->current_hospitalized_B_F = 0.0;
                                                                    it->current_TP_B_F = 0.0;
                                                                    it->current_symptomatic_B_F = 0.0;
                                                                    it->exposed_asymptomatic_B_F = it->current_exposed_asymptomatic_B_F;
                                                                    it->false_positive_B_F = 0.0;
                                                                    it->false_positive_RU_B_F = 0.0;
                                                                    it->true_positive_B_F = 0.0;
                                                                    it->symptomatic_infected_B_F = 0.0;

                                                                    myfile_infections_table << OMEGA * 100 << "%" << "\t" << U_N_F_0 << "\t" << U_N_S_0 << "\t" << U_W_F_0 << "\t" << U_W_S_0 << "\t" << U_B_F_0 << "\t" << U_B_S_0 << "\t" << ETA << "\t" << GAMMA;
                                                                    myfile_screening_table << OMEGA * 100 << "%" << "\t" << U_N_F_0 << "\t" << U_N_S_0 << "\t" << U_W_F_0 << "\t" << U_W_S_0 << "\t" << U_B_F_0 << "\t" << U_B_S_0 << "\t" << ETA << "\t" << GAMMA;

                                                                    if (TAU_N_S == TAU_N_F && TAU_W_S == TAU_W_F && TAU_B_S == TAU_B_F && ((TAU_W_S == TAU_N_S) || (TAU_W_S == 0)) && ((TAU_B_S == TAU_N_S) || (TAU_B_S == 0)))
                                                                    {
                                                                        customized_scenarios_filtered << OMEGA * 100 << "%" << "\t" << U_N_F_0 << "\t" << U_N_S_0 << "\t" << U_W_F_0 << "\t" << U_W_S_0 << "\t" << U_B_F_0 << "\t" << U_B_S_0 << "\t" << ETA << "\t" << GAMMA;
                                                                    }



                                                                    if (LAMBDA == 0)
                                                                    {
                                                                        myfile_infections_table << "\t" << 0;
                                                                        myfile_screening_table << "\t" << 0;
                                                                        if (TAU_N_S == TAU_N_F && TAU_W_S == TAU_W_F && TAU_B_S == TAU_B_F && ((TAU_W_S == TAU_N_S) || (TAU_W_S == 0)) && ((TAU_B_S == TAU_N_S) || (TAU_B_S == 0)))
                                                                        {
                                                                            customized_scenarios_filtered << "\t" << 0;
                                                                        }
                                                                    }
                                                                    else
                                                                    {
                                                                        myfile_infections_table << "\t" << 1.0 / (3 * LAMBDA * 7);
                                                                        myfile_screening_table << "\t" << 1.0 / (3 * LAMBDA * 7);
                                                                        if (TAU_N_S == TAU_N_F && TAU_W_S == TAU_W_F && TAU_B_S == TAU_B_F && ((TAU_W_S == TAU_N_S) || (TAU_W_S == 0)) && ((TAU_B_S == TAU_N_S) || (TAU_B_S == 0)))
                                                                        {
                                                                            customized_scenarios_filtered << "\t" << 1.0 / (3 * LAMBDA * 7);
                                                                        }

                                                                    }

                                                                    if (TAU_N_S == 0) {
                                                                        myfile_infections_table << "\t" << "N/A";
                                                                        myfile_screening_table << "\t" << "N/A";
                                                                        if (TAU_N_S == TAU_N_F && TAU_W_S == TAU_W_F && TAU_B_S == TAU_B_F && ((TAU_W_S == TAU_N_S) || (TAU_W_S == 0)) && ((TAU_B_S == TAU_N_S) || (TAU_B_S == 0)))
                                                                        {
                                                                            customized_scenarios_filtered << "\t" << 0;
                                                                        }

                                                                    }
                                                                    else {
                                                                        myfile_infections_table << "\t" << 1.0 / (3 * TAU_N_S);
                                                                        myfile_screening_table << "\t" << 1.0 / (3 * TAU_N_S);
                                                                        if (TAU_N_S == TAU_N_F && TAU_W_S == TAU_W_F && TAU_B_S == TAU_B_F && ((TAU_W_S == TAU_N_S) || (TAU_W_S == 0)) && ((TAU_B_S == TAU_N_S) || (TAU_B_S == 0)))
                                                                        {
                                                                            customized_scenarios_filtered << "\t" << 1.0 / (3 * TAU_N_S);
                                                                        }

                                                                    }
                                                                    if (TAU_W_S == 0)
                                                                    {
                                                                        myfile_infections_table << "\t" << "N/A";
                                                                        myfile_screening_table << "\t" << "N/A";
                                                                        if (TAU_N_S == TAU_N_F && TAU_W_S == TAU_W_F && TAU_B_S == TAU_B_F && ((TAU_W_S == TAU_N_S) || (TAU_W_S == 0)) && ((TAU_B_S == TAU_N_S) || (TAU_B_S == 0)))
                                                                        {
                                                                            customized_scenarios_filtered << "\t" << 0;
                                                                        }

                                                                    }
                                                                    else {
                                                                        myfile_infections_table << "\t" << 1.0 / (3 * TAU_W_S);
                                                                        myfile_screening_table << "\t" << 1.0 / (3 * TAU_W_S);
                                                                        if (TAU_N_S == TAU_N_F && TAU_W_S == TAU_W_F && TAU_B_S == TAU_B_F && ((TAU_W_S == TAU_N_S) || (TAU_W_S == 0)) && ((TAU_B_S == TAU_N_S) || (TAU_B_S == 0)))
                                                                        {
                                                                            customized_scenarios_filtered << "\t" << 1.0 / (3 * TAU_W_S);
                                                                        }

                                                                    }
                                                                    if (TAU_B_S == 0) {
                                                                        myfile_infections_table << "\t" << "N/A";
                                                                        myfile_screening_table << "\t" << "N/A";
                                                                        if (TAU_N_S == TAU_N_F && TAU_W_S == TAU_W_F && TAU_B_S == TAU_B_F && ((TAU_W_S == TAU_N_S) || (TAU_W_S == 0)) && ((TAU_B_S == TAU_N_S) || (TAU_B_S == 0)))
                                                                        {
                                                                            customized_scenarios_filtered << "\t" << 0;
                                                                        }

                                                                    }
                                                                    else
                                                                    {
                                                                        myfile_infections_table << "\t" << 1.0 / (3 * TAU_B_S);
                                                                        myfile_screening_table << "\t" << 1.0 / (3 * TAU_B_S);
                                                                        if (TAU_N_S == TAU_N_F && TAU_W_S == TAU_W_F && TAU_B_S == TAU_B_F && ((TAU_W_S == TAU_N_S) || (TAU_W_S == 0)) && ((TAU_B_S == TAU_N_S) || (TAU_B_S == 0)))
                                                                        {
                                                                            customized_scenarios_filtered << "\t" << 1.0 / (3 * TAU_B_S);
                                                                        }

                                                                    }

                                                                    if (TAU_N_F == 0) {
                                                                        myfile_infections_table << "\t" << "N/A";
                                                                        myfile_screening_table << "\t" << "N/A";
                                                                        if (TAU_N_S == TAU_N_F && TAU_W_S == TAU_W_F && TAU_B_S == TAU_B_F && ((TAU_W_S == TAU_N_S) || (TAU_W_S == 0)) && ((TAU_B_S == TAU_N_S) || (TAU_B_S == 0)))
                                                                        {
                                                                            customized_scenarios_filtered << "\t" << 0;
                                                                        }

                                                                    }
                                                                    else {
                                                                        myfile_infections_table << "\t" << 1.0 / (3 * TAU_N_F);
                                                                        myfile_screening_table << "\t" << 1.0 / (3 * TAU_N_F);
                                                                        if (TAU_N_S == TAU_N_F && TAU_W_S == TAU_W_F && TAU_B_S == TAU_B_F && ((TAU_W_S == TAU_N_S) || (TAU_W_S == 0)) && ((TAU_B_S == TAU_N_S) || (TAU_B_S == 0)))
                                                                        {
                                                                            customized_scenarios_filtered << "\t" << 1.0 / (3 * TAU_N_F);
                                                                        }

                                                                    }
                                                                    if (TAU_W_F == 0)
                                                                    {
                                                                        myfile_infections_table << "\t" << "N/A";
                                                                        myfile_screening_table << "\t" << "N/A";
                                                                        if (TAU_N_S == TAU_N_F && TAU_W_S == TAU_W_F && TAU_B_S == TAU_B_F && ((TAU_W_S == TAU_N_S) || (TAU_W_S == 0)) && ((TAU_B_S == TAU_N_S) || (TAU_B_S == 0)))
                                                                        {
                                                                            customized_scenarios_filtered << "\t" << 0;
                                                                        }

                                                                    }
                                                                    else {
                                                                        myfile_infections_table << "\t" << 1.0 / (3 * TAU_W_F);
                                                                        myfile_screening_table << "\t" << 1.0 / (3 * TAU_W_F);
                                                                        if (TAU_N_S == TAU_N_F && TAU_W_S == TAU_W_F && TAU_B_S == TAU_B_F && ((TAU_W_S == TAU_N_S) || (TAU_W_S == 0)) && ((TAU_B_S == TAU_N_S) || (TAU_B_S == 0)))
                                                                        {
                                                                            customized_scenarios_filtered << "\t" << 1.0 / (3 * TAU_W_F);
                                                                        }

                                                                    }
                                                                    if (TAU_B_F == 0) {
                                                                        myfile_infections_table << "\t" << "N/A";
                                                                        myfile_screening_table << "\t" << "N/A";
                                                                        if (TAU_N_S == TAU_N_F && TAU_W_S == TAU_W_F && TAU_B_S == TAU_B_F && ((TAU_W_S == TAU_N_S) || (TAU_W_S == 0)) && ((TAU_B_S == TAU_N_S) || (TAU_B_S == 0)))
                                                                        {
                                                                            customized_scenarios_filtered << "\t" << 0;
                                                                        }
                                                                    }
                                                                    else
                                                                    {
                                                                        myfile_infections_table << "\t" << 1.0 / (3 * TAU_B_F);
                                                                        myfile_screening_table << "\t" << 1.0 / (3 * TAU_B_F);
                                                                        if (TAU_N_S == TAU_N_F && TAU_W_S == TAU_W_F && TAU_B_S == TAU_B_F && ((TAU_W_S == TAU_N_S) || (TAU_W_S == 0)) && ((TAU_B_S == TAU_N_S) || (TAU_B_S == 0)))
                                                                        {
                                                                            customized_scenarios_filtered << "\t" << 1.0 / (3 * TAU_B_F);
                                                                        }
                                                                    }


                                                                }

                                                                else
                                                                {
                                                                    cout << "ERROR! " << endl;
                                                                    break;
                                                                }
                                                                //rates initializations
                                                                /*it->hospitalization_rate_N_S = 0.0;
                                                                it->hospitalization_rate_N_F = 0.0;
                                                                it->hospitalization_rate_W_S = 0.0;
                                                                it->hospitalization_rate_W_F = 0.0;
                                                                it->hospitalization_rate_B_S = 0.0;
                                                                it->hospitalization_rate_B_F = 0.0;

                                                                it->fatality_rate_N_S = 0.0;
                                                                it->fatality_rate_N_F = 0.0;
                                                                it->fatality_rate_W_S = 0.0;
                                                                it->fatality_rate_W_F = 0.0;
                                                                it->fatality_rate_B_S = 0.0;
                                                                it->fatality_rate_B_F = 0.0;

                                                                R_0_N_S = 0.0;
                                                                R_0_N_F = 0.0;
                                                                R_0_W_S = 0.0;
                                                                R_0_W_F = 0.0;
                                                                R_0_B_S = 0.0;
                                                                R_0_B_F = 0.0;

                                                                BETA_NS_NS_t = 0.0;
                                                                BETA_NF_NS_t = 0.0;
                                                                BETA_WS_NS_t = 0.0;
                                                                BETA_WF_NS_t = 0.0;
                                                                BETA_BS_NS_t = 0.0;
                                                                BETA_BF_NS_t = 0.0;

                                                                BETA_NS_NF_t = 0.0;
                                                                BETA_NF_NF_t = 0.0;
                                                                BETA_WS_NF_t = 0.0;
                                                                BETA_WF_NF_t = 0.0;
                                                                BETA_BS_NF_t = 0.0;
                                                                BETA_BF_NF_t = 0.0;

                                                                BETA_NS_WS_t = 0.0;
                                                                BETA_NF_WS_t = 0.0;
                                                                BETA_WS_WS_t = 0.0;
                                                                BETA_WF_WS_t = 0.0;
                                                                BETA_BS_WS_t = 0.0;
                                                                BETA_BF_WS_t = 0.0;

                                                                BETA_NS_WF_t = 0.0;
                                                                BETA_NF_WF_t = 0.0;
                                                                BETA_WS_WF_t = 0.0;
                                                                BETA_WF_WF_t = 0.0;
                                                                BETA_BS_WF_t = 0.0;
                                                                BETA_BF_WF_t = 0.0;

                                                                BETA_NS_BS_t = 0.0;
                                                                BETA_NF_BS_t = 0.0;
                                                                BETA_WS_BS_t = 0.0;
                                                                BETA_WF_BS_t = 0.0;
                                                                BETA_BS_BS_t = 0.0;
                                                                BETA_BF_BS_t = 0.0;

                                                                BETA_NS_BF_t = 0.0;
                                                                BETA_NF_BF_t = 0.0;
                                                                BETA_WS_BF_t = 0.0;
                                                                BETA_WF_BF_t = 0.0;
                                                                BETA_BS_BF_t = 0.0;
                                                                BETA_BF_BF_t = 0.0;*/

                                                                

                                                                EPSILON_W = 0.8 * (1 - OMEGA) + 0.33 * OMEGA;
                                                                EPSILON_B = 0.867 * (1 - OMEGA) + 0.694 * OMEGA;
                                                                UPSILON_W = 0.917 * (1 - OMEGA) + 0.7 * OMEGA;
                                                                UPSILON_B = 0.975 * (1 - OMEGA) + 0.93 * OMEGA;

                                                                R_0_N_S = R0_S_Delta * (1 - OMEGA) + 3 * R0_S_Delta * OMEGA;
                                                                R_0_W_S = R0_S_Delta * (1 - OMEGA) + 3 * R0_S_Delta * OMEGA;
                                                                R_0_B_S = R0_S_Delta * (1 - OMEGA) + 3 * R0_S_Delta * OMEGA;
                                                                R_0_N_F = R0_F_Delta * (1 - OMEGA) + 3 * R0_F_Delta * OMEGA;
                                                                R_0_W_F = R0_F_Delta * (1 - OMEGA) + 3 * R0_F_Delta * OMEGA;
                                                                R_0_B_F = R0_F_Delta * (1 - OMEGA) + 3 * R0_F_Delta * OMEGA;


                                                                N_U_t = it->uninfected_N_S + it->uninfected_N_F + it->uninfected_W_S + it->uninfected_W_F + it->uninfected_B_S + it->uninfected_B_F;

                                                                R_NS_NS_t = (1 - GAMMA) * R_0_N_S * it->uninfected_N_S / N_U_t;
                                                                R_NF_NS_t = (1 - GAMMA) * R_0_N_F * it->uninfected_N_S / N_U_t;
                                                                R_WS_NS_t = (1 - GAMMA) * R_0_W_S * it->uninfected_N_S / N_U_t;
                                                                R_WF_NS_t = (1 - GAMMA) * R_0_W_F * it->uninfected_N_S / N_U_t;
                                                                R_BS_NS_t = (1 - GAMMA) * R_0_B_S * it->uninfected_N_S / N_U_t;
                                                                R_BF_NS_t = (1 - GAMMA) * R_0_B_F * it->uninfected_N_S / N_U_t;

                                                                R_NS_NF_t = (1 - GAMMA) * R_0_N_S * it->uninfected_N_F / N_U_t;
                                                                R_NF_NF_t = (1 - GAMMA) * R_0_N_F * it->uninfected_N_F / N_U_t;
                                                                R_WS_NF_t = (1 - GAMMA) * R_0_W_S * it->uninfected_N_F / N_U_t;
                                                                R_WF_NF_t = (1 - GAMMA) * R_0_W_F * it->uninfected_N_F / N_U_t;
                                                                R_BS_NF_t = (1 - GAMMA) * R_0_B_S * it->uninfected_N_F / N_U_t;
                                                                R_BF_NF_t = (1 - GAMMA) * R_0_B_F * it->uninfected_N_F / N_U_t;

                                                                R_NS_WS_t = (1 - GAMMA) * R_0_N_S * (1 - EPSILON_W) * it->uninfected_W_S / N_U_t;
                                                                R_NF_WS_t = (1 - GAMMA) * R_0_N_F * (1 - EPSILON_W) * it->uninfected_W_S / N_U_t;
                                                                R_WS_WS_t = (1 - GAMMA) * R_0_W_S * (1 - EPSILON_W) * it->uninfected_W_S / N_U_t;
                                                                R_WF_WS_t = (1 - GAMMA) * R_0_W_F * (1 - EPSILON_W) * it->uninfected_W_S / N_U_t;
                                                                R_BS_WS_t = (1 - GAMMA) * R_0_B_S * (1 - EPSILON_W) * it->uninfected_W_S / N_U_t;
                                                                R_BF_WS_t = (1 - GAMMA) * R_0_B_F * (1 - EPSILON_W) * it->uninfected_W_S / N_U_t;

                                                                R_NS_WF_t = (1 - GAMMA) * R_0_N_S * (1 - EPSILON_W) * it->uninfected_W_F / N_U_t;
                                                                R_NF_WF_t = (1 - GAMMA) * R_0_N_F * (1 - EPSILON_W) * it->uninfected_W_F / N_U_t;
                                                                R_WS_WF_t = (1 - GAMMA) * R_0_W_S * (1 - EPSILON_W) * it->uninfected_W_F / N_U_t;
                                                                R_WF_WF_t = (1 - GAMMA) * R_0_W_F * (1 - EPSILON_W) * it->uninfected_W_F / N_U_t;
                                                                R_BS_WF_t = (1 - GAMMA) * R_0_B_S * (1 - EPSILON_W) * it->uninfected_W_F / N_U_t;
                                                                R_BF_WF_t = (1 - GAMMA) * R_0_B_F * (1 - EPSILON_W) * it->uninfected_W_F / N_U_t;

                                                                R_NS_BS_t = (1 - GAMMA) * R_0_N_S * (1 - EPSILON_B) * it->uninfected_B_S / N_U_t;
                                                                R_NF_BS_t = (1 - GAMMA) * R_0_N_F * (1 - EPSILON_B) * it->uninfected_B_S / N_U_t;
                                                                R_WS_BS_t = (1 - GAMMA) * R_0_W_S * (1 - EPSILON_B) * it->uninfected_B_S / N_U_t;
                                                                R_WF_BS_t = (1 - GAMMA) * R_0_W_F * (1 - EPSILON_B) * it->uninfected_B_S / N_U_t;
                                                                R_BS_BS_t = (1 - GAMMA) * R_0_B_S * (1 - EPSILON_B) * it->uninfected_B_S / N_U_t;
                                                                R_BF_BS_t = (1 - GAMMA) * R_0_B_F * (1 - EPSILON_B) * it->uninfected_B_S / N_U_t;

                                                                R_NS_BF_t = (1 - GAMMA) * R_0_N_S * (1 - EPSILON_B) * it->uninfected_B_F / N_U_t;
                                                                R_NF_BF_t = (1 - GAMMA) * R_0_N_F * (1 - EPSILON_B) * it->uninfected_B_F / N_U_t;
                                                                R_WS_BF_t = (1 - GAMMA) * R_0_W_S * (1 - EPSILON_B) * it->uninfected_B_F / N_U_t;
                                                                R_WF_BF_t = (1 - GAMMA) * R_0_W_F * (1 - EPSILON_B) * it->uninfected_B_F / N_U_t;
                                                                R_BS_BF_t = (1 - GAMMA) * R_0_B_S * (1 - EPSILON_B) * it->uninfected_B_F / N_U_t;
                                                                R_BF_BF_t = (1 - GAMMA) * R_0_B_F * (1 - EPSILON_B) * it->uninfected_B_F / N_U_t;


                                                                BETA_NS_NS_t = R_NS_NS_t * (SIGMA_N + RHO_N);
                                                                BETA_NF_NS_t = R_NF_NS_t * (SIGMA_N + RHO_N);
                                                                BETA_WS_NS_t = R_WS_NS_t * (SIGMA_N + RHO_N);
                                                                BETA_WF_NS_t = R_WF_NS_t * (SIGMA_N + RHO_N);
                                                                BETA_BS_NS_t = R_BS_NS_t * (SIGMA_N + RHO_N);
                                                                BETA_BF_NS_t = R_BF_NS_t * (SIGMA_N + RHO_N);

                                                                BETA_NS_NF_t = R_NS_NF_t * (SIGMA_N + RHO_N);
                                                                BETA_NF_NF_t = R_NF_NF_t * (SIGMA_N + RHO_N);
                                                                BETA_WS_NF_t = R_WS_NF_t * (SIGMA_N + RHO_N);
                                                                BETA_WF_NF_t = R_WF_NF_t * (SIGMA_N + RHO_N);
                                                                BETA_BS_NF_t = R_BS_NF_t * (SIGMA_N + RHO_N);
                                                                BETA_BF_NF_t = R_BF_NF_t * (SIGMA_N + RHO_N);

                                                                BETA_NS_WS_t = R_NS_WS_t * (SIGMA_W + RHO_W);
                                                                BETA_NF_WS_t = R_NF_WS_t * (SIGMA_W + RHO_W);
                                                                BETA_WS_WS_t = R_WS_WS_t * (SIGMA_W + RHO_W);
                                                                BETA_WF_WS_t = R_WF_WS_t * (SIGMA_W + RHO_W);
                                                                BETA_BS_WS_t = R_BS_WS_t * (SIGMA_W + RHO_W);
                                                                BETA_BF_WS_t = R_BF_WS_t * (SIGMA_W + RHO_W);

                                                                BETA_NS_WF_t = R_NS_WF_t * (SIGMA_W + RHO_W);
                                                                BETA_NF_WF_t = R_NF_WF_t * (SIGMA_W + RHO_W);
                                                                BETA_WS_WF_t = R_WS_WF_t * (SIGMA_W + RHO_W);
                                                                BETA_WF_WF_t = R_WF_WF_t * (SIGMA_W + RHO_W);
                                                                BETA_BS_WF_t = R_BS_WF_t * (SIGMA_W + RHO_W);
                                                                BETA_BF_WF_t = R_BF_WF_t * (SIGMA_W + RHO_W);

                                                                BETA_NS_BS_t = R_NS_BS_t * (SIGMA_B + RHO_B);
                                                                BETA_NF_BS_t = R_NF_BS_t * (SIGMA_B + RHO_B);
                                                                BETA_WS_BS_t = R_WS_BS_t * (SIGMA_B + RHO_B);
                                                                BETA_WF_BS_t = R_WF_BS_t * (SIGMA_B + RHO_B);
                                                                BETA_BS_BS_t = R_BS_BS_t * (SIGMA_B + RHO_B);
                                                                BETA_BF_BS_t = R_BF_BS_t * (SIGMA_B + RHO_B);

                                                                BETA_NS_BF_t = R_NS_BF_t * (SIGMA_B + RHO_B);
                                                                BETA_NF_BF_t = R_NF_BF_t * (SIGMA_B + RHO_B);
                                                                BETA_WS_BF_t = R_WS_BF_t * (SIGMA_B + RHO_B);
                                                                BETA_WF_BF_t = R_WF_BF_t * (SIGMA_B + RHO_B);
                                                                BETA_BS_BF_t = R_BS_BF_t * (SIGMA_B + RHO_B);
                                                                BETA_BF_BF_t = R_BF_BF_t * (SIGMA_B + RHO_B);


                                                                it->hospitalization_rate_N_S = 0.014;
                                                                it->hospitalization_rate_W_S = 0.014 * (1 - UPSILON_W);
                                                                it->hospitalization_rate_B_S = 0.014 * (1 - UPSILON_B);
                                                                it->hospitalization_rate_N_F = 0.084;
                                                                it->hospitalization_rate_W_F = 0.084 * (1 - UPSILON_W);
                                                                it->hospitalization_rate_B_F = 0.084 * (1 - UPSILON_B);

                                                                it->fatality_rate_N_S = 0.0005;
                                                                it->fatality_rate_W_S = 0.0005 * (1 - 1.002 * UPSILON_W);
                                                                it->fatality_rate_B_S = 0.0005 * (1 - 1.002 * UPSILON_B);
                                                                it->fatality_rate_N_F = 0.02;
                                                                it->fatality_rate_W_F = 0.02 * (1 - 1.002 * UPSILON_W);
                                                                it->fatality_rate_B_F = 0.02 * (1 - 1.002 * UPSILON_B);


                                                                PI_N_S = RHO_N * it->hospitalization_rate_N_S / ((SIGMA_N / (RHO_N + SIGMA_N)) - it->hospitalization_rate_N_S);
                                                                PI_N_F = RHO_N * it->hospitalization_rate_N_F / ((SIGMA_N / (RHO_N + SIGMA_N)) - it->hospitalization_rate_N_F);
                                                                PI_W_S = RHO_W * it->hospitalization_rate_W_S / ((SIGMA_W / (RHO_W + SIGMA_W)) - it->hospitalization_rate_W_S);
                                                                PI_W_F = RHO_W * it->hospitalization_rate_W_F / ((SIGMA_W / (RHO_W + SIGMA_W)) - it->hospitalization_rate_W_F);
                                                                PI_B_S = RHO_B * it->hospitalization_rate_B_S / ((SIGMA_B / (RHO_B + SIGMA_B)) - it->hospitalization_rate_B_S);
                                                                PI_B_F = RHO_B * it->hospitalization_rate_B_F / ((SIGMA_B / (RHO_B + SIGMA_B)) - it->hospitalization_rate_B_F);


                                                                DELTA_N_S = RHO_N * it->fatality_rate_N_S / ((SIGMA_N / (RHO_N + SIGMA_N)) * (PI_N_S / (RHO_N + PI_N_S)) - it->fatality_rate_N_S);
                                                                DELTA_N_F = RHO_N * it->fatality_rate_N_F / ((SIGMA_N / (RHO_N + SIGMA_N)) * (PI_N_F / (RHO_N + PI_N_F)) - it->fatality_rate_N_F);
                                                                DELTA_W_S = RHO_W * it->fatality_rate_W_S / ((SIGMA_W / (RHO_W + SIGMA_W)) * (PI_W_S / (RHO_W + PI_W_S)) - it->fatality_rate_W_S);
                                                                DELTA_W_F = RHO_W * it->fatality_rate_W_F / ((SIGMA_W / (RHO_W + SIGMA_W)) * (PI_W_F / (RHO_W + PI_W_F)) - it->fatality_rate_W_F);
                                                                DELTA_B_S = RHO_B * it->fatality_rate_B_S / ((SIGMA_B / (RHO_B + SIGMA_B)) * (PI_B_S / (RHO_B + PI_B_S)) - it->fatality_rate_B_S);
                                                                DELTA_B_F = RHO_B * it->fatality_rate_B_F / ((SIGMA_B / (RHO_B + SIGMA_B)) * (PI_B_F / (RHO_B + PI_B_F)) - it->fatality_rate_B_F);



                                                                it->indicator_N_S = 0.0;
                                                                it->indicator_N_F = 0.0;
                                                                it->indicator_W_S = 0.0;
                                                                it->indicator_W_F = 0.0;
                                                                it->indicator_B_S = 0.0;
                                                                it->indicator_B_F = 0.0;
                                                                it->max_sum_infections_combined = 0.0;
                                                                it->day_max_sum_infections_combined = 0.0;
                                                                it->max_sum_hospitalized_combined = 0.0;
                                                                it->day_max_sum_hospitalized_combined = 0.0;
                                                                it->cumul_infections_combined = 0.0;
                                                                it->cumul_hospitalization_combined = 0.0;
                                                                it->cumul_deaths_combined = 0.0;
                                                                it->average_screening_tests_used_combined = 0.0;
                                                                it->cumul_screening_tests_used_combined = 0.0;

                                                                it->cumul_asymptomatic_N_S = 0.0;
                                                                it->cumul_infections_N_S = 0.0;
                                                                it->infections_N_S = 0.0;
                                                                it->max_infections_N_S = 0.0;
                                                                it->cumul_hospitalization_N_S = 0.0;
                                                                it->cumul_deaths_N_S = 0.0;
                                                                it->day_max_infections_N_S = 0.0;
                                                                it->previous_RU_N_S = 0;
                                                                it->current_RU_N_S = 0;
                                                                it->current_RK_N_S = it->recovered_known_N_S;
                                                                it->cumul_screening_tests_used_N_S = 0.0;
                                                                it->average_screening_tests_used_N_S = 0.0;


                                                                it->cumul_asymptomatic_N_F = 0.0;
                                                                it->cumul_infections_N_F = 0.0;
                                                                it->infections_N_F = 0.0;
                                                                it->max_infections_N_F = 0.0;
                                                                it->cumul_hospitalization_N_F = 0.0;
                                                                it->cumul_deaths_N_F = 0.0;
                                                                it->day_max_infections_N_F = 0.0;
                                                                it->previous_RU_N_F = 0;
                                                                it->current_RU_N_F = 0;
                                                                it->current_RK_N_F = it->recovered_known_N_F;
                                                                it->cumul_screening_tests_used_N_F = 0.0;
                                                                it->average_screening_tests_used_N_F = 0.0;



                                                                it->cumul_infections_no_immunity = 0.0;
                                                                it->cumul_hospitalization_no_immunity = 0.0;
                                                                it->cumul_deaths_no_immunity = 0.0;
                                                                it->max_sum_infections_no_immunity = 0.0;
                                                                it->max_sum_hospitalized_no_immunity = 0.0;
                                                                it->day_max_sum_hospitalized_no_immunity = 0.0;
                                                                it->day_max_sum_infections_no_immunity = 0.0;
                                                                it->average_screening_tests_used_no_immunity = 0.0;
                                                                it->cumul_screening_tests_used_no_immunity = 0.0;

                                                                it->cumul_asymptomatic_W_S = 0.0;
                                                                it->cumul_infections_W_S = 0.0;
                                                                it->infections_W_S = 0.0;
                                                                it->max_infections_W_S = 0.0;
                                                                it->cumul_hospitalization_W_S = 0.0;
                                                                it->cumul_deaths_W_S = 0.0;
                                                                it->day_max_infections_W_S = 0.0;
                                                                it->previous_RU_W_S = 0;
                                                                it->current_RU_W_S = 0;
                                                                it->current_RK_W_S = it->recovered_known_W_S;
                                                                it->cumul_screening_tests_used_W_S = 0.0;
                                                                it->average_screening_tests_used_W_S = 0.0;



                                                                it->cumul_asymptomatic_W_F = 0.0;
                                                                it->cumul_infections_W_F = 0.0;
                                                                it->infections_W_F = 0.0;
                                                                it->max_infections_W_F = 0.0;
                                                                it->cumul_hospitalization_W_F = 0.0;
                                                                it->cumul_deaths_W_F = 0.0;
                                                                it->day_max_infections_W_F = 0.0;
                                                                it->previous_RU_W_F = 0;
                                                                it->current_RU_W_F = 0;
                                                                it->current_RK_W_F = it->recovered_known_W_F;
                                                                it->cumul_screening_tests_used_W_F = 0.0;
                                                                it->average_screening_tests_used_W_F = 0.0;



                                                                it->cumul_infections_waning_immunity = 0.0;
                                                                it->cumul_hospitalization_waning_immunity = 0.0;
                                                                it->cumul_deaths_waning_immunity = 0.0;
                                                                it->max_sum_infections_waning_immunity = 0.0;
                                                                it->max_sum_hospitalized_waning_immunity = 0.0;
                                                                it->day_max_sum_hospitalized_waning_immunity = 0.0;
                                                                it->day_max_sum_infections_waning_immunity = 0.0;
                                                                it->average_screening_tests_used_waning_immunity = 0.0;
                                                                it->cumul_screening_tests_used_waning_immunity = 0.0;

                                                                it->cumul_asymptomatic_B_S = 0.0;
                                                                it->cumul_infections_B_S = 0.0;
                                                                it->infections_B_S = 0.0;
                                                                it->max_infections_B_S = 0.0;
                                                                it->cumul_hospitalization_B_S = 0.0;
                                                                it->cumul_deaths_B_S = 0.0;
                                                                it->day_max_infections_B_S = 0.0;
                                                                it->previous_RU_B_S = 0;
                                                                it->current_RU_B_S = 0;
                                                                it->current_RK_B_S = it->recovered_known_B_S;
                                                                it->cumul_screening_tests_used_B_S = 0.0;
                                                                it->average_screening_tests_used_B_S = 0.0;



                                                                it->cumul_asymptomatic_B_F = 0.0;
                                                                it->cumul_infections_B_F = 0.0;
                                                                it->infections_B_F = 0.0;
                                                                it->max_infections_B_F = 0.0;
                                                                it->cumul_hospitalization_B_F = 0.0;
                                                                it->cumul_deaths_B_F = 0.0;
                                                                it->day_max_infections_B_F = 0.0;
                                                                it->previous_RU_B_F = 0;
                                                                it->current_RU_B_F = 0;
                                                                it->current_RK_B_F = it->recovered_known_B_F;
                                                                it->cumul_screening_tests_used_B_F = 0.0;
                                                                it->average_screening_tests_used_B_F = 0.0;



                                                                it->cumul_infections_boosted_immunity = 0.0;
                                                                it->cumul_hospitalization_boosted_immunity = 0.0;
                                                                it->cumul_deaths_boosted_immunity = 0.0;
                                                                it->max_sum_infections_boosted_immunity = 0.0;
                                                                it->max_sum_hospitalized_boosted_immunity = 0.0;
                                                                it->day_max_sum_hospitalized_boosted_immunity = 0.0;
                                                                it->day_max_sum_infections_boosted_immunity = 0.0;
                                                                it->average_screening_tests_used_boosted_immunity = 0.0;
                                                                it->cumul_screening_tests_used_boosted_immunity = 0.0;
                                                                it->ratio_per_100_tests = 0.0;
                                                                it->ratio_of_peak_per_100_tests = 0.0;



                                                                if (it->current_uninfected_N_S == 0 && it->current_exposed_asymptomatic_N_S == 0 && it->current_asymptomatic_N_S == 0 && it->current_RK_N_S == 0 && it->current_RU_N_S == 0)
                                                                {
                                                                    it->ratio_N_S = 0;
                                                                }
                                                                else it->ratio_N_S = 1 / (1.0 * (it->current_uninfected_N_S + it->current_exposed_asymptomatic_N_S + it->current_asymptomatic_N_S + it->current_RK_N_S + it->current_RU_N_S));


                                                                if (it->current_uninfected_N_F == 0 && it->current_exposed_asymptomatic_N_F == 0 && it->current_asymptomatic_N_F == 0 && it->current_RK_N_F == 0 && it->current_RU_N_F == 0)
                                                                {
                                                                    it->ratio_N_F = 0;
                                                                }
                                                                else it->ratio_N_F = 1 / (1.0 * (it->current_uninfected_N_F + it->current_exposed_asymptomatic_N_F + it->current_asymptomatic_N_F + it->current_RK_N_F + it->current_RU_N_F));


                                                                if (it->current_uninfected_W_S == 0 && it->current_exposed_asymptomatic_W_S == 0 && it->current_asymptomatic_W_S == 0 && it->current_RK_W_S == 0 && it->current_RU_W_S == 0)
                                                                {
                                                                    it->ratio_W_S = 0;
                                                                }
                                                                else it->ratio_W_S = 1 / (1.0 * (it->current_uninfected_W_S + it->current_exposed_asymptomatic_W_S + it->current_asymptomatic_W_S + it->current_RK_W_S + it->current_RU_W_S));


                                                                if (it->current_uninfected_W_F == 0 && it->current_exposed_asymptomatic_W_F == 0 && it->current_asymptomatic_W_F == 0 && it->current_RK_W_F == 0 && it->current_RU_W_F == 0)
                                                                {
                                                                    it->ratio_W_F = 0;
                                                                }
                                                                else it->ratio_W_F = 1 / (1.0 * (it->current_uninfected_W_F + it->current_exposed_asymptomatic_W_F + it->current_asymptomatic_W_F + it->current_RK_W_F + it->current_RU_W_F));


                                                                if (it->current_uninfected_B_S == 0 && it->current_exposed_asymptomatic_B_S == 0 && it->current_asymptomatic_B_S == 0 && it->current_RK_B_S == 0 && it->current_RU_B_S == 0)
                                                                {
                                                                    it->ratio_B_S = 0;
                                                                }
                                                                else  it->ratio_B_S = 1 / (1.0 * (it->current_uninfected_B_S + it->current_exposed_asymptomatic_B_S + it->current_asymptomatic_B_S + it->current_RK_B_S + it->current_RU_B_S));


                                                                if (it->current_uninfected_B_F == 0 && it->current_exposed_asymptomatic_B_F == 0 && it->current_asymptomatic_B_F == 0 && it->current_RK_B_F == 0 && it->current_RU_B_F == 0)
                                                                {
                                                                    it->ratio_B_F = 0;
                                                                }
                                                                else  it->ratio_B_F = 1 / (1.0 * (it->current_uninfected_B_F + it->current_exposed_asymptomatic_B_F + it->current_asymptomatic_B_F + it->current_RK_B_F + it->current_RU_B_F));


                                                            } //end of initialization

                                                            if (i / 3 == (7 * week_N_S - 1) && (it->current_uninfected_N_S * (1 - BETA_NS_NS_t * it->ratio_N_S * it->current_asymptomatic_N_S - BETA_NF_NS_t * it->ratio_N_S * it->current_asymptomatic_N_F - BETA_WS_NS_t * it->ratio_N_S * it->current_asymptomatic_W_S - BETA_WF_NS_t * it->ratio_N_S * it->current_asymptomatic_W_F - BETA_BS_NS_t * it->ratio_N_S * it->current_asymptomatic_B_S - BETA_BF_NS_t * it->ratio_N_S * it->current_asymptomatic_B_F) - it->previous_uninfected_N_S * TAU_N_S * ETA * (1 - Sp) + MU * it->false_positive_N_S - X_N_S) > 0)
                                                            {
                                                                it->indicator_N_S = 1.0; //=1 to consider exogenous shocks
                                                                week_N_S++;

                                                            }
                                                            else
                                                            {

                                                                it->indicator_N_S = 0.0;
                                                            }

                                                            if (i / 3 == (7 * week_N_F - 1) && (it->current_uninfected_N_F * (1 - BETA_NS_NF_t * it->ratio_N_F * it->current_asymptomatic_N_S - BETA_NF_NF_t * it->ratio_N_F * it->current_asymptomatic_N_F - BETA_WS_NF_t * it->ratio_N_F * it->current_asymptomatic_W_S - BETA_WF_NF_t * it->ratio_N_F * it->current_asymptomatic_W_F - BETA_BS_NF_t * it->ratio_N_F * it->current_asymptomatic_B_S - BETA_BF_NF_t * it->ratio_N_F * it->current_asymptomatic_B_F) - it->previous_uninfected_N_F * TAU_N_F * ETA * (1 - Sp) + MU * it->false_positive_N_F - X_N_F) > 0)
                                                            {
                                                                it->indicator_N_F = 1.0; //=1 to consider exogenous shocks
                                                                week_N_F++;
                                                            }
                                                            else
                                                            {

                                                                it->indicator_N_F = 0.0;
                                                            }

                                                            if (i / 3 == (7 * week_W_S - 1) && (it->current_uninfected_W_S * (1 - BETA_NS_WS_t * it->ratio_W_S * it->current_asymptomatic_N_S - BETA_NF_WS_t * it->ratio_W_S * it->current_asymptomatic_N_F - BETA_WS_WS_t * it->ratio_W_S * it->current_asymptomatic_W_S - BETA_WF_WS_t * it->ratio_W_S * it->current_asymptomatic_W_F - BETA_BS_WS_t * it->ratio_W_S * it->current_asymptomatic_B_S - BETA_BF_WS_t * it->ratio_W_S * it->current_asymptomatic_B_F - LAMBDA) - it->previous_uninfected_W_S * TAU_W_S * ETA * (1 - Sp) + MU * it->false_positive_W_S - X_W_S) > 0)
                                                            {
                                                                it->indicator_W_S = 1.0; //=1 to consider exogenous shocks 
                                                                week_W_S++;
                                                            }
                                                            else
                                                            {

                                                                it->indicator_W_S = 0.0;
                                                            }

                                                            if (i / 3 == (7 * week_W_F - 1) && (it->current_uninfected_W_F * (1 - BETA_NS_WF_t * it->ratio_W_F * it->current_asymptomatic_N_S - BETA_NF_WF_t * it->ratio_W_F * it->current_asymptomatic_N_F - BETA_WS_WF_t * it->ratio_W_F * it->current_asymptomatic_W_S - BETA_WF_WF_t * it->ratio_W_F * it->current_asymptomatic_W_F - BETA_BS_WF_t * it->ratio_W_F * it->current_asymptomatic_B_S - BETA_BF_WF_t * it->ratio_W_F * it->current_asymptomatic_B_F - LAMBDA) - it->previous_uninfected_W_F * TAU_W_F * ETA * (1 - Sp) + MU * it->false_positive_W_F - X_W_F) > 0)
                                                            {
                                                                it->indicator_W_F = 1.0; //=1 to consider exogenous shocks
                                                                week_W_F++;
                                                            }
                                                            else
                                                            {

                                                                it->indicator_W_F = 0.0;
                                                            }
                                                            if (i / 3 == (7 * week_B_S - 1) && (it->current_uninfected_B_S * (1 - BETA_NS_BS_t * it->ratio_B_S * it->current_asymptomatic_N_S - BETA_NF_BS_t * it->ratio_B_S * it->current_asymptomatic_N_F - BETA_WS_BS_t * it->ratio_B_S * it->current_asymptomatic_W_S - BETA_WF_BS_t * it->ratio_B_S * it->current_asymptomatic_W_F - BETA_BS_BS_t * it->ratio_B_S * it->current_asymptomatic_B_S - BETA_BF_BS_t * it->ratio_B_S * it->current_asymptomatic_B_F) - it->previous_uninfected_B_S * TAU_B_S * ETA * (1 - Sp) + LAMBDA * it->uninfected_W_S + MU * it->false_positive_B_S - X_B_S) > 0)
                                                            {
                                                                it->indicator_B_S = 1.0; //=1 to consider exogenous shocks
                                                                week_B_S++;
                                                            }
                                                            else
                                                            {

                                                                it->indicator_B_S = 0.0;
                                                            }

                                                            if (i / 3 == (7 * week_B_F - 1) && (it->current_uninfected_B_F * (1 - BETA_NS_BF_t * it->ratio_B_F * it->current_asymptomatic_N_S - BETA_NF_BF_t * it->ratio_B_F * it->current_asymptomatic_N_F - BETA_WS_BF_t * it->ratio_B_F * it->current_asymptomatic_W_S - BETA_WF_BF_t * it->ratio_B_F * it->current_asymptomatic_W_F - BETA_BS_BF_t * it->ratio_B_F * it->current_asymptomatic_B_S - BETA_BF_BF_t * it->ratio_B_F * it->current_asymptomatic_B_F) - it->previous_uninfected_B_F * TAU_B_F * ETA * (1 - Sp) + LAMBDA * it->uninfected_W_F + MU * it->false_positive_B_F - X_B_F) > 0)
                                                            {
                                                                it->indicator_B_F = 1.0; //=1 to consider exogenous shocks
                                                                week_B_F++;
                                                            }
                                                            else
                                                            {

                                                                it->indicator_B_F = 0.0;
                                                            }


                                                            
                                                            //STUDENTS
                                                // No immunity - Students COMPARTMENTS:  it->current_asymptomatic_N_S
                                                            it->uninfected_N_S = it->current_uninfected_N_S * (1 - it->ratio_N_S * (BETA_NS_NS_t * it->current_asymptomatic_N_S + BETA_NF_NS_t * it->current_asymptomatic_N_F + BETA_WS_NS_t * it->current_asymptomatic_W_S + BETA_WF_NS_t * it->current_asymptomatic_W_F + BETA_BS_NS_t * it->current_asymptomatic_B_S + BETA_BF_NS_t * it->current_asymptomatic_B_F)) - it->previous_uninfected_N_S * TAU_N_S * ETA * (1 - Sp) + MU * it->false_positive_N_S - X_N_S * 1.0 * it->indicator_N_S; //Fp here is current FP (not yet updated)

                                                            //cout <<  ( it->ratio_N_S * (BETA_NS_NS_t * it->current_asymptomatic_N_S - BETA_NF_NS_t * it->current_asymptomatic_N_F - BETA_WS_NS_t * it->current_asymptomatic_W_S - BETA_WF_NS_t * it->current_asymptomatic_W_F - BETA_BS_NS_t * it->current_asymptomatic_B_S - BETA_BF_NS_t * it->current_asymptomatic_B_F)) << endl; //Fp here is current FP (not yet updated)

                                                            it->asymptomatic_infected_N_S = it->current_asymptomatic_N_S * (1 - SIGMA_N - RHO_N) - it->previous_asymptomatic_infected_N_S * TAU_N_S * ETA * Se + it->current_exposed_asymptomatic_N_S * THETA;

                                                            it->exposed_asymptomatic_N_S = it->exposed_asymptomatic_N_S * (1 - THETA) + it->current_uninfected_N_S * it->ratio_N_S * (BETA_NS_NS_t * it->current_asymptomatic_N_S + BETA_NF_NS_t * it->current_asymptomatic_N_F + BETA_WS_NS_t * it->current_asymptomatic_W_S + BETA_WF_NS_t * it->current_asymptomatic_W_F + BETA_BS_NS_t * it->current_asymptomatic_B_S + BETA_BF_NS_t * it->current_asymptomatic_B_F) + 1.0 * X_N_S * it->indicator_N_S;

                                                            it->false_positive_N_S = it->false_positive_N_S * (1 - MU) + it->previous_uninfected_N_S * TAU_N_S * ETA * (1 - Sp);

                                                            it->recovered_unknown_N_S = it->recovered_unknown_N_S + RHO_N * it->current_asymptomatic_N_S - it->previous_RU_N_S * TAU_N_S * ETA * (1 - Sp) + MU * it->false_positive_RU_N_S;

                                                            it->hospitalized_N_S = it->hospitalized_N_S * (1 - RHO_N - DELTA_N_S) + PI_N_S * it->symptomatic_infected_N_S;

                                                            it->symptomatic_infected_N_S = it->symptomatic_infected_N_S * (1 - RHO_N - PI_N_S) + SIGMA_N * (it->true_positive_N_S + it->current_asymptomatic_N_S); //TP not yet updated

                                                            it->true_positive_N_S = it->true_positive_N_S * (1 - SIGMA_N - RHO_N) + it->previous_asymptomatic_infected_N_S * TAU_N_S * ETA * Se;

                                                            it->false_positive_RU_N_S = it->false_positive_RU_N_S * (1 - MU) + it->previous_RU_N_S * TAU_N_S * ETA * (1 - Sp);

                                                            it->recovered_known_N_S = it->recovered_known_N_S + RHO_N * (it->current_TP_N_S + it->current_symptomatic_N_S + it->current_hospitalized_N_S);

                                                            // it->uninfected_N_S + it->asymptomatic_infected_N_S + it->exposed_asymptomatic_N_S + it->false_positive_N_S + it->recovered_unknown_N_S + it->hospitalized_N_S + it->symptomatic_infected_N_S + it->true_positive_N_S + it->false_positive_RU_N_S + it->recovered_known_N_S;

                                                             // WANING immunity - Students COMPARTMENTS:
                                                            it->uninfected_W_S = it->current_uninfected_W_S * (1 - LAMBDA - it->ratio_W_S * (BETA_NS_WS_t * it->current_asymptomatic_N_S + BETA_NF_WS_t * it->current_asymptomatic_N_F + BETA_WS_WS_t * it->current_asymptomatic_W_S + BETA_WF_WS_t * it->current_asymptomatic_W_F + BETA_BS_WS_t * it->current_asymptomatic_B_S + BETA_BF_WS_t * it->current_asymptomatic_B_F)) - it->previous_uninfected_W_S * TAU_W_S * ETA * (1 - Sp) + MU * it->false_positive_W_S - X_W_S * 1.0 * it->indicator_W_S; //Fp here is current FP (not yet updated)

                                                            it->asymptomatic_infected_W_S = it->current_asymptomatic_W_S * (1 - SIGMA_W - RHO_W) - it->previous_asymptomatic_infected_W_S * TAU_W_S * ETA * Se + it->current_exposed_asymptomatic_W_S * THETA;

                                                            it->exposed_asymptomatic_W_S = it->exposed_asymptomatic_W_S * (1 - THETA) + it->current_uninfected_W_S * it->ratio_W_S * (BETA_NS_WS_t * it->current_asymptomatic_N_S + BETA_NF_WS_t * it->current_asymptomatic_N_F + BETA_WS_WS_t * it->current_asymptomatic_W_S + BETA_WF_WS_t * it->current_asymptomatic_W_F + BETA_BS_WS_t * it->current_asymptomatic_B_S + BETA_BF_WS_t * it->current_asymptomatic_B_F) + 1.0 * X_W_S * it->indicator_W_S;

                                                            it->false_positive_W_S = it->false_positive_W_S * (1 - MU) + it->previous_uninfected_W_S * TAU_W_S * ETA * (1 - Sp);

                                                            it->recovered_unknown_W_S = it->recovered_unknown_W_S + RHO_W * it->current_asymptomatic_W_S - it->previous_RU_W_S * TAU_W_S * ETA * (1 - Sp) + MU * it->false_positive_RU_W_S;

                                                            it->hospitalized_W_S = it->hospitalized_W_S * (1 - RHO_W - DELTA_W_S) + PI_W_S * it->symptomatic_infected_W_S;

                                                            it->symptomatic_infected_W_S = it->symptomatic_infected_W_S * (1 - RHO_W - PI_W_S) + SIGMA_W * (it->true_positive_W_S + it->current_asymptomatic_W_S); //TP not yet updated

                                                            it->true_positive_W_S = it->true_positive_W_S * (1 - SIGMA_W - RHO_W) + it->previous_asymptomatic_infected_W_S * TAU_W_S * ETA * Se;

                                                            it->false_positive_RU_W_S = it->false_positive_RU_W_S * (1 - MU) + it->previous_RU_W_S * TAU_W_S * ETA * (1 - Sp);

                                                            it->recovered_known_W_S = it->recovered_known_W_S + RHO_W * (it->current_TP_W_S + it->current_symptomatic_W_S + it->current_hospitalized_W_S);

                                                            // BOOSTED immunity - Students COMPARTMENTS:
                                                            it->uninfected_B_S = it->current_uninfected_B_S * (1 - it->ratio_B_S * (BETA_NS_BS_t * it->current_asymptomatic_N_S + BETA_NF_BS_t * it->current_asymptomatic_N_F + BETA_WS_BS_t * it->current_asymptomatic_W_S + BETA_WF_BS_t * it->current_asymptomatic_W_F + BETA_BS_BS_t * it->current_asymptomatic_B_S + BETA_BF_BS_t * it->current_asymptomatic_B_F)) - it->previous_uninfected_B_S * TAU_B_S * ETA * (1 - Sp) + LAMBDA * it->uninfected_W_S + MU * it->false_positive_B_S - X_B_S * 1.0 * it->indicator_B_S; //Fp here is current FP (not yet updated)

                                                            it->asymptomatic_infected_B_S = it->current_asymptomatic_B_S * (1 - SIGMA_B - RHO_B) - it->previous_asymptomatic_infected_B_S * TAU_B_S * ETA * Se + it->current_exposed_asymptomatic_B_S * THETA;

                                                            it->exposed_asymptomatic_B_S = it->exposed_asymptomatic_B_S * (1 - THETA) + it->current_uninfected_B_S * it->ratio_B_S * (BETA_NS_BS_t * it->current_asymptomatic_N_S + BETA_NF_BS_t * it->current_asymptomatic_N_F + BETA_WS_BS_t * it->current_asymptomatic_W_S + BETA_WF_BS_t * it->current_asymptomatic_W_F + BETA_BS_BS_t * it->current_asymptomatic_B_S + BETA_BF_BS_t * it->current_asymptomatic_B_F) + 1.0 * X_B_S * it->indicator_B_S;

                                                            it->false_positive_B_S = it->false_positive_B_S * (1 - MU) + it->previous_uninfected_B_S * TAU_B_S * ETA * (1 - Sp);

                                                            it->recovered_unknown_B_S = it->recovered_unknown_B_S + RHO_B * it->current_asymptomatic_B_S - it->previous_RU_B_S * TAU_B_S * ETA * (1 - Sp) + MU * it->false_positive_RU_B_S;

                                                            it->hospitalized_B_S = it->hospitalized_B_S * (1 - RHO_B - DELTA_B_S) + PI_B_S * it->symptomatic_infected_B_S;

                                                            it->symptomatic_infected_B_S = it->symptomatic_infected_B_S * (1 - RHO_B - PI_B_S) + SIGMA_B * (it->true_positive_B_S + it->current_asymptomatic_B_S); //TP not yet updated

                                                            it->true_positive_B_S = it->true_positive_B_S * (1 - SIGMA_B - RHO_B) + it->previous_asymptomatic_infected_B_S * TAU_B_S * ETA * Se;

                                                            it->false_positive_RU_B_S = it->false_positive_RU_B_S * (1 - MU) + it->previous_RU_B_S * TAU_B_S * ETA * (1 - Sp);

                                                            it->recovered_known_B_S = it->recovered_known_B_S + RHO_B * (it->current_TP_B_S + it->current_symptomatic_B_S + it->current_hospitalized_B_S);


                                                            it->dead_S = it->dead_S + DELTA_N_S * it->current_hospitalized_N_S + DELTA_W_S * it->current_hospitalized_W_S + DELTA_B_S * it->current_hospitalized_B_S;


                                                            //FACULTY
                                                            //No immunity - Faculty COMPARTMENTS:  
                                                            it->uninfected_N_F = it->current_uninfected_N_F * (1 - it->ratio_N_F * (BETA_NS_NF_t * it->current_asymptomatic_N_S + BETA_NF_NF_t * it->current_asymptomatic_N_F + BETA_WS_NF_t * it->current_asymptomatic_W_S + BETA_WF_NF_t * it->current_asymptomatic_W_F + BETA_BS_NF_t * it->current_asymptomatic_B_S + BETA_BF_NF_t * it->current_asymptomatic_B_F)) - it->previous_uninfected_N_F * TAU_N_F * ETA * (1 - Sp) + MU * it->false_positive_N_F - X_N_F * 1.0 * it->indicator_N_F; //Fp here is current FP (not yet updated)

                                                            it->asymptomatic_infected_N_F = it->current_asymptomatic_N_F * (1 - SIGMA_N - RHO_N) - it->previous_asymptomatic_infected_N_F * TAU_N_F * ETA * Se + it->current_exposed_asymptomatic_N_F * THETA;

                                                            it->exposed_asymptomatic_N_F = it->exposed_asymptomatic_N_F * (1 - THETA) + it->current_uninfected_N_F * it->ratio_N_F * (BETA_NS_NF_t * it->current_asymptomatic_N_S + BETA_NF_NF_t * it->current_asymptomatic_N_F + BETA_WS_NF_t * it->current_asymptomatic_W_S + BETA_WF_NF_t * it->current_asymptomatic_W_F + BETA_BS_NF_t * it->current_asymptomatic_B_S + BETA_BF_NF_t * it->current_asymptomatic_B_F) + 1.0 * X_N_F * it->indicator_N_F;

                                                            it->false_positive_N_F = it->false_positive_N_F * (1 - MU) + it->previous_uninfected_N_F * TAU_N_F * ETA * (1 - Sp);

                                                            it->recovered_unknown_N_F = it->recovered_unknown_N_F + RHO_N * it->current_asymptomatic_N_F - it->previous_RU_N_F * TAU_N_F * ETA * (1 - Sp) + MU * it->false_positive_RU_N_F;

                                                            it->hospitalized_N_F = it->hospitalized_N_F * (1 - RHO_N - DELTA_N_F) + PI_N_F * it->symptomatic_infected_N_F;

                                                            it->symptomatic_infected_N_F = it->symptomatic_infected_N_F * (1 - RHO_N - PI_N_F) + SIGMA_N * (it->true_positive_N_F + it->current_asymptomatic_N_F); //TP not yet updated

                                                            it->true_positive_N_F = it->true_positive_N_F * (1 - SIGMA_N - RHO_N) + it->previous_asymptomatic_infected_N_F * TAU_N_F * ETA * Se;

                                                            it->false_positive_RU_N_F = it->false_positive_RU_N_F * (1 - MU) + it->previous_RU_N_F * TAU_N_F * ETA * (1 - Sp);

                                                            it->recovered_known_N_F = it->recovered_known_N_F + RHO_N * (it->current_TP_N_F + it->current_symptomatic_N_F + it->current_hospitalized_N_F);


                                                            // WANING immunity - Faculty COMPARTMENTS:
                                                            it->uninfected_W_F = it->current_uninfected_W_F * (1 - LAMBDA - it->ratio_W_F * (BETA_NS_WF_t * it->current_asymptomatic_N_S + BETA_NF_WF_t * it->current_asymptomatic_N_F + BETA_WS_WF_t * it->current_asymptomatic_W_S + BETA_WF_WF_t * it->current_asymptomatic_W_F + BETA_BS_WF_t * it->current_asymptomatic_B_S + BETA_BF_WF_t * it->current_asymptomatic_B_F)) - it->previous_uninfected_W_F * TAU_W_F * ETA * (1 - Sp) + MU * it->false_positive_W_F - X_W_F * 1.0 * it->indicator_W_F; //Fp here is current FP (not yet updated)

                                                            it->asymptomatic_infected_W_F = it->current_asymptomatic_W_F * (1 - SIGMA_W - RHO_W) - it->previous_asymptomatic_infected_W_F * TAU_W_F * ETA * Se + it->current_exposed_asymptomatic_W_F * THETA;

                                                            it->exposed_asymptomatic_W_F = it->exposed_asymptomatic_W_F * (1 - THETA) + it->current_uninfected_W_F * it->ratio_W_F * (BETA_NS_WF_t * it->current_asymptomatic_N_S + BETA_NF_WF_t * it->current_asymptomatic_N_F + BETA_WS_WF_t * it->current_asymptomatic_W_S + BETA_WF_WF_t * it->current_asymptomatic_W_F + BETA_BS_WF_t * it->current_asymptomatic_B_S + BETA_BF_WF_t * it->current_asymptomatic_B_F) + 1.0 * X_W_F * it->indicator_W_F;

                                                            it->false_positive_W_F = it->false_positive_W_F * (1 - MU) + it->previous_uninfected_W_F * TAU_W_F * ETA * (1 - Sp);

                                                            it->recovered_unknown_W_F = it->recovered_unknown_W_F + RHO_W * it->current_asymptomatic_W_F - it->previous_RU_W_F * TAU_W_F * ETA * (1 - Sp) + MU * it->false_positive_RU_W_F;

                                                            it->hospitalized_W_F = it->hospitalized_W_F * (1 - RHO_W - DELTA_W_F) + PI_W_F * it->symptomatic_infected_W_F;

                                                            it->symptomatic_infected_W_F = it->symptomatic_infected_W_F * (1 - RHO_W - PI_W_F) + SIGMA_W * (it->true_positive_W_F + it->current_asymptomatic_W_F); //TP not yet updated

                                                            it->true_positive_W_F = it->true_positive_W_F * (1 - SIGMA_W - RHO_W) + it->previous_asymptomatic_infected_W_F * TAU_W_F * ETA * Se;

                                                            it->false_positive_RU_W_F = it->false_positive_RU_W_F * (1 - MU) + it->previous_RU_W_F * TAU_W_F * ETA * (1 - Sp);

                                                            it->recovered_known_W_F = it->recovered_known_W_F + RHO_W * (it->current_TP_W_F + it->current_symptomatic_W_F + it->current_hospitalized_W_F);

                                                            // BOOSTED immunity - Faculty COMPARTMENTS:
                                                            it->uninfected_B_F = it->current_uninfected_B_F * (1 - it->ratio_B_F * (BETA_NS_BF_t * it->current_asymptomatic_N_S + BETA_NF_BF_t * it->current_asymptomatic_N_F + BETA_WS_BF_t * it->current_asymptomatic_W_S + BETA_WF_BF_t * it->current_asymptomatic_W_F + BETA_BS_BF_t * it->current_asymptomatic_B_S + BETA_BF_BF_t * it->current_asymptomatic_B_F)) - it->previous_uninfected_B_F * TAU_B_F * ETA * (1 - Sp) + LAMBDA * it->uninfected_W_F + MU * it->false_positive_B_F - X_B_F * 1.0 * it->indicator_B_F; //Fp here is current FP (not yet updated)

                                                            it->asymptomatic_infected_B_F = it->current_asymptomatic_B_F * (1 - SIGMA_B - RHO_B) - it->previous_asymptomatic_infected_B_F * TAU_B_F * ETA * Se + it->current_exposed_asymptomatic_B_F * THETA;

                                                            it->exposed_asymptomatic_B_F = it->exposed_asymptomatic_B_F * (1 - THETA) + it->current_uninfected_B_F * it->ratio_B_F * (BETA_NS_BF_t * it->current_asymptomatic_N_S + BETA_NF_BF_t * it->current_asymptomatic_N_F + BETA_WS_BF_t * it->current_asymptomatic_W_S + BETA_WF_BF_t * it->current_asymptomatic_W_F + BETA_BS_BF_t * it->current_asymptomatic_B_S + BETA_BF_BF_t * it->current_asymptomatic_B_F) + 1.0 * X_B_F * it->indicator_B_F;

                                                            it->false_positive_B_F = it->false_positive_B_F * (1 - MU) + it->previous_uninfected_B_F * TAU_B_F * ETA * (1 - Sp);

                                                            it->recovered_unknown_B_F = it->recovered_unknown_B_F + RHO_B * it->current_asymptomatic_B_F - it->previous_RU_B_F * TAU_B_F * ETA * (1 - Sp) + MU * it->false_positive_RU_B_F;

                                                            it->hospitalized_B_F = it->hospitalized_B_F * (1 - RHO_B - DELTA_B_F) + PI_B_F * it->symptomatic_infected_B_F;

                                                            it->symptomatic_infected_B_F = it->symptomatic_infected_B_F * (1 - RHO_B - PI_B_F) + SIGMA_B * (it->true_positive_B_F + it->current_asymptomatic_B_F); //TP not yet updated

                                                            it->true_positive_B_F = it->true_positive_B_F * (1 - SIGMA_B - RHO_B) + it->previous_asymptomatic_infected_B_F * TAU_B_F * ETA * Se;

                                                            it->false_positive_RU_B_F = it->false_positive_RU_B_F * (1 - MU) + it->previous_RU_B_F * TAU_B_F * ETA * (1 - Sp);

                                                            it->recovered_known_B_F = it->recovered_known_B_F + RHO_B * (it->current_TP_B_F + it->current_symptomatic_B_F + it->current_hospitalized_B_F);


                                                            it->dead_F = it->dead_F + DELTA_N_F * it->current_hospitalized_N_F + DELTA_W_F * it->current_hospitalized_W_F + DELTA_B_F * it->current_hospitalized_B_F;

                                                            


                                                            if (it->uninfected_N_S < 0) it->uninfected_N_S = 0;
                                                            if (it->exposed_asymptomatic_N_S < 0) it->exposed_asymptomatic_N_S = 0;
                                                            if (it->asymptomatic_infected_N_S < 0) it->asymptomatic_infected_N_S = 0;
                                                            if (it->recovered_unknown_N_S < 0) it->recovered_unknown_N_S = 0;
                                                            if (it->uninfected_W_S < 0) it->uninfected_W_S = 0;
                                                            if (it->exposed_asymptomatic_W_S < 0) it->exposed_asymptomatic_W_S = 0;
                                                            if (it->asymptomatic_infected_W_S < 0) it->asymptomatic_infected_W_S = 0;
                                                            if (it->recovered_unknown_W_S < 0) it->recovered_unknown_W_S = 0;
                                                            if (it->uninfected_B_S < 0) it->uninfected_B_S = 0;
                                                            if (it->exposed_asymptomatic_B_S < 0) it->exposed_asymptomatic_B_S = 0;
                                                            if (it->asymptomatic_infected_B_S < 0) it->asymptomatic_infected_B_S = 0;
                                                            if (it->recovered_unknown_B_S < 0) it->recovered_unknown_B_S = 0;

                                                            if (it->uninfected_N_F < 0) it->uninfected_N_F = 0;
                                                            if (it->exposed_asymptomatic_N_F < 0) it->exposed_asymptomatic_N_F = 0;
                                                            if (it->asymptomatic_infected_N_F < 0) it->asymptomatic_infected_N_F = 0;
                                                            if (it->recovered_unknown_N_F < 0) it->recovered_unknown_N_F = 0;
                                                            if (it->uninfected_W_F < 0) it->uninfected_W_F = 0;
                                                            if (it->exposed_asymptomatic_W_F < 0) it->exposed_asymptomatic_W_F = 0;
                                                            if (it->asymptomatic_infected_W_F < 0) it->asymptomatic_infected_W_F = 0;
                                                            if (it->recovered_unknown_W_F < 0) it->recovered_unknown_W_F = 0;
                                                            if (it->uninfected_B_F < 0) it->uninfected_B_F = 0;
                                                            if (it->exposed_asymptomatic_B_F < 0) it->exposed_asymptomatic_B_F = 0;
                                                            if (it->asymptomatic_infected_B_F < 0) it->asymptomatic_infected_B_F = 0;
                                                            if (it->recovered_unknown_B_F < 0) it->recovered_unknown_B_F = 0;

                                                            //Calculate # infections
                                                            it->infections_N_S = it->current_uninfected_N_S * it->ratio_N_S * (BETA_NS_NS_t * it->current_asymptomatic_N_S + BETA_NF_NS_t * it->current_asymptomatic_N_F + BETA_WS_NS_t * it->current_asymptomatic_W_S + BETA_WF_NS_t * it->current_asymptomatic_W_F + BETA_BS_NS_t * it->current_asymptomatic_B_S + BETA_BF_NS_t * it->current_asymptomatic_B_F);
                                                            it->infections_N_F = it->current_uninfected_N_F * it->ratio_N_F * (BETA_NS_NF_t * it->current_asymptomatic_N_S + BETA_NF_NF_t * it->current_asymptomatic_N_F + BETA_WS_NF_t * it->current_asymptomatic_W_S + BETA_WF_NF_t * it->current_asymptomatic_W_F + BETA_BS_NF_t * it->current_asymptomatic_B_S + BETA_BF_NF_t * it->current_asymptomatic_B_F);
                                                            it->infections_W_S = it->current_uninfected_W_S * it->ratio_W_S * (BETA_NS_WS_t * it->current_asymptomatic_N_S + BETA_NF_WS_t * it->current_asymptomatic_N_F + BETA_WS_WS_t * it->current_asymptomatic_W_S + BETA_WF_WS_t * it->current_asymptomatic_W_F + BETA_BS_WS_t * it->current_asymptomatic_B_S + BETA_BF_WS_t * it->current_asymptomatic_B_F);
                                                            it->infections_W_F = it->current_uninfected_W_F * it->ratio_W_F * (BETA_NS_WF_t * it->current_asymptomatic_N_S + BETA_NF_WF_t * it->current_asymptomatic_N_F + BETA_WS_WF_t * it->current_asymptomatic_W_S + BETA_WF_WF_t * it->current_asymptomatic_W_F + BETA_BS_WF_t * it->current_asymptomatic_B_S + BETA_BF_WF_t * it->current_asymptomatic_B_F);
                                                            it->infections_B_S = it->current_uninfected_B_S * it->ratio_B_S * (BETA_NS_BS_t * it->current_asymptomatic_N_S + BETA_NF_BS_t * it->current_asymptomatic_N_F + BETA_WS_BS_t * it->current_asymptomatic_W_S + BETA_WF_BS_t * it->current_asymptomatic_W_F + BETA_BS_BS_t * it->current_asymptomatic_B_S + BETA_BF_BS_t * it->current_asymptomatic_B_F);
                                                            it->infections_B_F = it->current_uninfected_B_F * it->ratio_B_F * (BETA_NS_BF_t * it->current_asymptomatic_N_S + BETA_NF_BF_t * it->current_asymptomatic_N_F + BETA_WS_BF_t * it->current_asymptomatic_W_S + BETA_WF_BF_t * it->current_asymptomatic_W_F + BETA_BS_BF_t * it->current_asymptomatic_B_S + BETA_BF_BF_t * it->current_asymptomatic_B_F);



                                                            if (it->uninfected_N_S == 0 && it->exposed_asymptomatic_N_S == 0 && it->asymptomatic_infected_N_S == 0 && it->recovered_known_N_S == 0 && it->recovered_unknown_N_S == 0)
                                                            {
                                                                it->ratio_N_S = 0;
                                                            }
                                                            else it->ratio_N_S = 1 / (1.0 * (it->uninfected_N_S + it->exposed_asymptomatic_N_S + it->asymptomatic_infected_N_S + it->recovered_known_N_S + it->recovered_unknown_N_S));

                                                            if (it->uninfected_N_F == 0 && it->exposed_asymptomatic_N_F == 0 && it->asymptomatic_infected_N_F == 0 && it->recovered_known_N_F == 0 && it->recovered_unknown_N_F == 0)
                                                            {
                                                                it->ratio_N_F = 0;
                                                            }
                                                            else
                                                            {
                                                                it->ratio_N_F = 1 / (1.0 * (it->uninfected_N_F + it->exposed_asymptomatic_N_F + it->asymptomatic_infected_N_F + it->recovered_known_N_F + it->recovered_unknown_N_F));

                                                            }

                                                            if (it->uninfected_W_S == 0 && it->exposed_asymptomatic_W_S == 0 && it->asymptomatic_infected_W_S == 0 && it->recovered_known_W_S == 0 && it->recovered_unknown_W_S == 0)
                                                            {
                                                                it->ratio_W_S = 0;

                                                            }
                                                            else it->ratio_W_S = 1 / (1.0 * (it->uninfected_W_S + it->exposed_asymptomatic_W_S + it->asymptomatic_infected_W_S + it->recovered_known_W_S + it->recovered_unknown_W_S));

                                                            if (it->uninfected_W_F == 0 && it->exposed_asymptomatic_W_F == 0 && it->asymptomatic_infected_W_F == 0 && it->recovered_known_W_F == 0 && it->recovered_unknown_W_F == 0)
                                                            {
                                                                it->ratio_W_F = 0;
                                                            }
                                                            else
                                                            {
                                                                it->ratio_W_F = 1 / (1.0 * (it->uninfected_W_F + it->exposed_asymptomatic_W_F + it->asymptomatic_infected_W_F + it->recovered_known_W_F + it->recovered_unknown_W_F));

                                                            }

                                                            if (it->uninfected_B_S == 0 && it->exposed_asymptomatic_B_S == 0 && it->asymptomatic_infected_B_S == 0 && it->recovered_known_B_S == 0 && it->recovered_unknown_B_S == 0)
                                                            {
                                                                it->ratio_B_S = 0;

                                                            }
                                                            else it->ratio_B_S = 1 / (1.0 * (it->uninfected_B_S + it->exposed_asymptomatic_B_S + it->asymptomatic_infected_B_S + it->recovered_known_B_S + it->recovered_unknown_B_S));

                                                            if (it->uninfected_B_F == 0 && it->exposed_asymptomatic_B_F == 0 && it->asymptomatic_infected_B_F == 0 && it->recovered_known_B_F == 0 && it->recovered_unknown_B_F == 0)
                                                            {
                                                                it->ratio_B_F = 0;
                                                            }
                                                            else
                                                            {
                                                                it->ratio_B_F = 1 / (1.0 * (it->uninfected_B_F + it->exposed_asymptomatic_B_F + it->asymptomatic_infected_B_F + it->recovered_known_B_F + it->recovered_unknown_B_F));

                                                            }


                                                          
                                                           


                                                            N_U_t = it->uninfected_N_S + it->uninfected_N_F + it->uninfected_W_S + it->uninfected_W_F + it->uninfected_B_S + it->uninfected_B_F;

                                                            R_NS_NS_t = (1 - GAMMA) * R_0_N_S * it->uninfected_N_S / N_U_t;
                                                            R_NF_NS_t = (1 - GAMMA) * R_0_N_F * it->uninfected_N_S / N_U_t;
                                                            R_WS_NS_t = (1 - GAMMA) * R_0_W_S * it->uninfected_N_S / N_U_t;
                                                            R_WF_NS_t = (1 - GAMMA) * R_0_W_F * it->uninfected_N_S / N_U_t;
                                                            R_BS_NS_t = (1 - GAMMA) * R_0_B_S * it->uninfected_N_S / N_U_t;
                                                            R_BF_NS_t = (1 - GAMMA) * R_0_B_F * it->uninfected_N_S / N_U_t;

                                                            R_NS_NF_t = (1 - GAMMA) * R_0_N_S * it->uninfected_N_F / N_U_t;
                                                            R_NF_NF_t = (1 - GAMMA) * R_0_N_F * it->uninfected_N_F / N_U_t;
                                                            R_WS_NF_t = (1 - GAMMA) * R_0_W_S * it->uninfected_N_F / N_U_t;
                                                            R_WF_NF_t = (1 - GAMMA) * R_0_W_F * it->uninfected_N_F / N_U_t;
                                                            R_BS_NF_t = (1 - GAMMA) * R_0_B_S * it->uninfected_N_F / N_U_t;
                                                            R_BF_NF_t = (1 - GAMMA) * R_0_B_F * it->uninfected_N_F / N_U_t;

                                                            R_NS_WS_t = (1 - GAMMA) * R_0_N_S * (1 - EPSILON_W) * it->uninfected_W_S / N_U_t;
                                                            R_NF_WS_t = (1 - GAMMA) * R_0_N_F * (1 - EPSILON_W) * it->uninfected_W_S / N_U_t;
                                                            R_WS_WS_t = (1 - GAMMA) * R_0_W_S * (1 - EPSILON_W) * it->uninfected_W_S / N_U_t;
                                                            R_WF_WS_t = (1 - GAMMA) * R_0_W_F * (1 - EPSILON_W) * it->uninfected_W_S / N_U_t;
                                                            R_BS_WS_t = (1 - GAMMA) * R_0_B_S * (1 - EPSILON_W) * it->uninfected_W_S / N_U_t;
                                                            R_BF_WS_t = (1 - GAMMA) * R_0_B_F * (1 - EPSILON_W) * it->uninfected_W_S / N_U_t;

                                                            R_NS_WF_t = (1 - GAMMA) * R_0_N_S * (1 - EPSILON_W) * it->uninfected_W_F / N_U_t;
                                                            R_NF_WF_t = (1 - GAMMA) * R_0_N_F * (1 - EPSILON_W) * it->uninfected_W_F / N_U_t;
                                                            R_WS_WF_t = (1 - GAMMA) * R_0_W_S * (1 - EPSILON_W) * it->uninfected_W_F / N_U_t;
                                                            R_WF_WF_t = (1 - GAMMA) * R_0_W_F * (1 - EPSILON_W) * it->uninfected_W_F / N_U_t;
                                                            R_BS_WF_t = (1 - GAMMA) * R_0_B_S * (1 - EPSILON_W) * it->uninfected_W_F / N_U_t;
                                                            R_BF_WF_t = (1 - GAMMA) * R_0_B_F * (1 - EPSILON_W) * it->uninfected_W_F / N_U_t;

                                                            R_NS_BS_t = (1 - GAMMA) * R_0_N_S * (1 - EPSILON_B) * it->uninfected_B_S / N_U_t;
                                                            R_NF_BS_t = (1 - GAMMA) * R_0_N_F * (1 - EPSILON_B) * it->uninfected_B_S / N_U_t;
                                                            R_WS_BS_t = (1 - GAMMA) * R_0_W_S * (1 - EPSILON_B) * it->uninfected_B_S / N_U_t;
                                                            R_WF_BS_t = (1 - GAMMA) * R_0_W_F * (1 - EPSILON_B) * it->uninfected_B_S / N_U_t;
                                                            R_BS_BS_t = (1 - GAMMA) * R_0_B_S * (1 - EPSILON_B) * it->uninfected_B_S / N_U_t;
                                                            R_BF_BS_t = (1 - GAMMA) * R_0_B_F * (1 - EPSILON_B) * it->uninfected_B_S / N_U_t;

                                                            R_NS_BF_t = (1 - GAMMA) * R_0_N_S * (1 - EPSILON_B) * it->uninfected_B_F / N_U_t;
                                                            R_NF_BF_t = (1 - GAMMA) * R_0_N_F * (1 - EPSILON_B) * it->uninfected_B_F / N_U_t;
                                                            R_WS_BF_t = (1 - GAMMA) * R_0_W_S * (1 - EPSILON_B) * it->uninfected_B_F / N_U_t;
                                                            R_WF_BF_t = (1 - GAMMA) * R_0_W_F * (1 - EPSILON_B) * it->uninfected_B_F / N_U_t;
                                                            R_BS_BF_t = (1 - GAMMA) * R_0_B_S * (1 - EPSILON_B) * it->uninfected_B_F / N_U_t;
                                                            R_BF_BF_t = (1 - GAMMA) * R_0_B_F * (1 - EPSILON_B) * it->uninfected_B_F / N_U_t;


                                                            BETA_NS_NS_t = R_NS_NS_t * (SIGMA_N + RHO_N);
                                                            BETA_NF_NS_t = R_NF_NS_t * (SIGMA_N + RHO_N);
                                                            BETA_WS_NS_t = R_WS_NS_t * (SIGMA_N + RHO_N);
                                                            BETA_WF_NS_t = R_WF_NS_t * (SIGMA_N + RHO_N);
                                                            BETA_BS_NS_t = R_BS_NS_t * (SIGMA_N + RHO_N);
                                                            BETA_BF_NS_t = R_BF_NS_t * (SIGMA_N + RHO_N);

                                                            BETA_NS_NF_t = R_NS_NF_t * (SIGMA_N + RHO_N);
                                                            BETA_NF_NF_t = R_NF_NF_t * (SIGMA_N + RHO_N);
                                                            BETA_WS_NF_t = R_WS_NF_t * (SIGMA_N + RHO_N);
                                                            BETA_WF_NF_t = R_WF_NF_t * (SIGMA_N + RHO_N);
                                                            BETA_BS_NF_t = R_BS_NF_t * (SIGMA_N + RHO_N);
                                                            BETA_BF_NF_t = R_BF_NF_t * (SIGMA_N + RHO_N);

                                                            BETA_NS_WS_t = R_NS_WS_t * (SIGMA_W + RHO_W);
                                                            BETA_NF_WS_t = R_NF_WS_t * (SIGMA_W + RHO_W);
                                                            BETA_WS_WS_t = R_WS_WS_t * (SIGMA_W + RHO_W);
                                                            BETA_WF_WS_t = R_WF_WS_t * (SIGMA_W + RHO_W);
                                                            BETA_BS_WS_t = R_BS_WS_t * (SIGMA_W + RHO_W);
                                                            BETA_BF_WS_t = R_BF_WS_t * (SIGMA_W + RHO_W);

                                                            BETA_NS_WF_t = R_NS_WF_t * (SIGMA_W + RHO_W);
                                                            BETA_NF_WF_t = R_NF_WF_t * (SIGMA_W + RHO_W);
                                                            BETA_WS_WF_t = R_WS_WF_t * (SIGMA_W + RHO_W);
                                                            BETA_WF_WF_t = R_WF_WF_t * (SIGMA_W + RHO_W);
                                                            BETA_BS_WF_t = R_BS_WF_t * (SIGMA_W + RHO_W);
                                                            BETA_BF_WF_t = R_BF_WF_t * (SIGMA_W + RHO_W);

                                                            BETA_NS_BS_t = R_NS_BS_t * (SIGMA_B + RHO_B);
                                                            BETA_NF_BS_t = R_NF_BS_t * (SIGMA_B + RHO_B);
                                                            BETA_WS_BS_t = R_WS_BS_t * (SIGMA_B + RHO_B);
                                                            BETA_WF_BS_t = R_WF_BS_t * (SIGMA_B + RHO_B);
                                                            BETA_BS_BS_t = R_BS_BS_t * (SIGMA_B + RHO_B);
                                                            BETA_BF_BS_t = R_BF_BS_t * (SIGMA_B + RHO_B);

                                                            BETA_NS_BF_t = R_NS_BF_t * (SIGMA_B + RHO_B);
                                                            BETA_NF_BF_t = R_NF_BF_t * (SIGMA_B + RHO_B);
                                                            BETA_WS_BF_t = R_WS_BF_t * (SIGMA_B + RHO_B);
                                                            BETA_WF_BF_t = R_WF_BF_t * (SIGMA_B + RHO_B);
                                                            BETA_BS_BF_t = R_BS_BF_t * (SIGMA_B + RHO_B);
                                                            BETA_BF_BF_t = R_BF_BF_t * (SIGMA_B + RHO_B);


                                                            it->hospitalization_rate_N_S = 0.014;
                                                            it->hospitalization_rate_W_S = 0.014 * (1 - UPSILON_W);
                                                            it->hospitalization_rate_B_S = 0.014 * (1 - UPSILON_B);
                                                            it->hospitalization_rate_N_F = 0.084;
                                                            it->hospitalization_rate_W_F = 0.084 * (1 - UPSILON_W);
                                                            it->hospitalization_rate_B_F = 0.084 * (1 - UPSILON_B);

                                                            it->fatality_rate_N_S = 0.0005;
                                                            it->fatality_rate_W_S = 0.0005 * (1 - 1.002 * UPSILON_W);
                                                            it->fatality_rate_B_S = 0.0005 * (1 - 1.002 * UPSILON_B);
                                                            it->fatality_rate_N_F = 0.02;
                                                            it->fatality_rate_W_F = 0.02 * (1 - 1.002 * UPSILON_W);
                                                            it->fatality_rate_B_F = 0.02 * (1 - 1.002 * UPSILON_B);


                                                            PI_N_S = RHO_N * it->hospitalization_rate_N_S / ((SIGMA_N / (RHO_N + SIGMA_N)) - it->hospitalization_rate_N_S);
                                                            PI_N_F = RHO_N * it->hospitalization_rate_N_F / ((SIGMA_N / (RHO_N + SIGMA_N)) - it->hospitalization_rate_N_F);
                                                            PI_W_S = RHO_W * it->hospitalization_rate_W_S / ((SIGMA_W / (RHO_W + SIGMA_W)) - it->hospitalization_rate_W_S);
                                                            PI_W_F = RHO_W * it->hospitalization_rate_W_F / ((SIGMA_W / (RHO_W + SIGMA_W)) - it->hospitalization_rate_W_F);
                                                            PI_B_S = RHO_B * it->hospitalization_rate_B_S / ((SIGMA_B / (RHO_B + SIGMA_B)) - it->hospitalization_rate_B_S);
                                                            PI_B_F = RHO_B * it->hospitalization_rate_B_F / ((SIGMA_B / (RHO_B + SIGMA_B)) - it->hospitalization_rate_B_F);


                                                            DELTA_N_S = RHO_N * it->fatality_rate_N_S / ((SIGMA_N / (RHO_N + SIGMA_N)) * (PI_N_S / (RHO_N + PI_N_S)) - it->fatality_rate_N_S);
                                                            DELTA_N_F = RHO_N * it->fatality_rate_N_F / ((SIGMA_N / (RHO_N + SIGMA_N)) * (PI_N_F / (RHO_N + PI_N_F)) - it->fatality_rate_N_F);
                                                            DELTA_W_S = RHO_W * it->fatality_rate_W_S / ((SIGMA_W / (RHO_W + SIGMA_W)) * (PI_W_S / (RHO_W + PI_W_S)) - it->fatality_rate_W_S);
                                                            DELTA_W_F = RHO_W * it->fatality_rate_W_F / ((SIGMA_W / (RHO_W + SIGMA_W)) * (PI_W_F / (RHO_W + PI_W_F)) - it->fatality_rate_W_F);
                                                            DELTA_B_S = RHO_B * it->fatality_rate_B_S / ((SIGMA_B / (RHO_B + SIGMA_B)) * (PI_B_S / (RHO_B + PI_B_S)) - it->fatality_rate_B_S);
                                                            DELTA_B_F = RHO_B * it->fatality_rate_B_F / ((SIGMA_B / (RHO_B + SIGMA_B)) * (PI_B_F / (RHO_B + PI_B_F)) - it->fatality_rate_B_F);


                                                            //TESTS
                                                            it->cumul_screening_tests_used_N_S = it->cumul_screening_tests_used_N_S + (it->current_uninfected_N_S + it->current_exposed_asymptomatic_N_S + it->current_asymptomatic_N_S + it->current_RU_N_S) * TAU_N_S * ETA;
                                                            it->cumul_screening_tests_used_N_F = it->cumul_screening_tests_used_N_F + (it->current_uninfected_N_F + it->current_exposed_asymptomatic_N_F + it->current_asymptomatic_N_F + it->current_RU_N_F) * TAU_N_F * ETA;
                                                            it->cumul_screening_tests_used_W_S = it->cumul_screening_tests_used_W_S + (it->current_uninfected_W_S + it->current_exposed_asymptomatic_W_S + it->current_asymptomatic_W_S + it->current_RU_W_S) * TAU_W_S * ETA;
                                                            it->cumul_screening_tests_used_W_F = it->cumul_screening_tests_used_W_F + (it->current_uninfected_W_F + it->current_exposed_asymptomatic_W_F + it->current_asymptomatic_W_F + it->current_RU_W_F) * TAU_W_F * ETA;
                                                            it->cumul_screening_tests_used_B_S = it->cumul_screening_tests_used_B_S + (it->current_uninfected_B_S + it->current_exposed_asymptomatic_B_S + it->current_asymptomatic_B_S + it->current_RU_B_S) * TAU_B_S * ETA;
                                                            it->cumul_screening_tests_used_B_F = it->cumul_screening_tests_used_B_F + (it->current_uninfected_B_F + it->current_exposed_asymptomatic_B_F + it->current_asymptomatic_B_F + it->current_RU_B_F) * TAU_B_F * ETA;

                                                            it->cumul_screening_tests_used_no_immunity = it->cumul_screening_tests_used_no_immunity + (it->current_uninfected_N_S + it->current_exposed_asymptomatic_N_S + it->current_asymptomatic_N_S + it->current_RU_N_S) * TAU_N_S * ETA + (it->current_uninfected_N_F + it->current_exposed_asymptomatic_N_F + it->current_asymptomatic_N_F + it->current_RU_N_F) * TAU_N_F * ETA;
                                                            it->cumul_screening_tests_used_waning_immunity = it->cumul_screening_tests_used_waning_immunity + (it->current_uninfected_W_S + it->current_exposed_asymptomatic_W_S + it->current_asymptomatic_W_S + it->current_RU_W_S) * TAU_W_S * ETA + (it->current_uninfected_W_F + it->current_exposed_asymptomatic_W_F + it->current_asymptomatic_W_F + it->current_RU_W_F) * TAU_W_F * ETA;
                                                            it->cumul_screening_tests_used_boosted_immunity = it->cumul_screening_tests_used_boosted_immunity + (it->current_uninfected_B_S + it->current_exposed_asymptomatic_B_S + it->current_asymptomatic_B_S + it->current_RU_B_S) * TAU_B_S * ETA + (it->current_uninfected_B_F + it->current_exposed_asymptomatic_B_F + it->current_asymptomatic_B_F + it->current_RU_B_F) * TAU_B_F * ETA;
                                                            it->cumul_screening_tests_used_combined = it->cumul_screening_tests_used_combined + (it->current_uninfected_N_S + it->current_exposed_asymptomatic_N_S + it->current_asymptomatic_N_S + it->current_RU_N_S) * TAU_N_S * ETA + (it->current_uninfected_N_F + it->current_exposed_asymptomatic_N_F + it->current_asymptomatic_N_F + it->current_RU_N_F) * TAU_N_F * ETA + (it->current_uninfected_W_S + it->current_exposed_asymptomatic_W_S + it->current_asymptomatic_W_S + it->current_RU_W_S) * TAU_W_S * ETA + (it->current_uninfected_W_F + it->current_exposed_asymptomatic_W_F + it->current_asymptomatic_W_F + it->current_RU_W_F) * TAU_W_F * ETA + (it->current_uninfected_B_S + it->current_exposed_asymptomatic_B_S + it->current_asymptomatic_B_S + it->current_RU_B_S) * TAU_B_S * ETA + (it->current_uninfected_B_F + it->current_exposed_asymptomatic_B_F + it->current_asymptomatic_B_F + it->current_RU_B_F) * TAU_B_F * ETA;


                                                            //Peak Calculations:
                                                            //Peak infections of subjects with no immunity
                                                            if ((it->infections_N_S + it->infections_N_F) > it->max_sum_infections_no_immunity)
                                                            {
                                                                it->max_sum_infections_no_immunity = (it->infections_N_S + it->infections_N_F);
                                                                it->day_max_sum_infections_no_immunity = disp_period_num + 1;
                                                            }

                                                            //Peak infections of subjects with waning immunity
                                                            if ((it->infections_W_S + it->infections_W_F) > it->max_sum_infections_waning_immunity)
                                                            {
                                                                it->max_sum_infections_waning_immunity = (it->infections_W_S + it->infections_W_F);
                                                                it->day_max_sum_infections_waning_immunity = disp_period_num + 1;
                                                            }

                                                            //Peak infections of subjects with boosted immunity
                                                            if ((it->infections_B_S + it->infections_B_F) > it->max_sum_infections_boosted_immunity)
                                                            {
                                                                it->max_sum_infections_boosted_immunity = (it->infections_B_S + it->infections_B_F);
                                                                it->day_max_sum_infections_boosted_immunity = disp_period_num + 1;
                                                            }

                                                            //Peak of total infections (combined)
                                                            if ((it->infections_N_S + it->infections_N_F + it->infections_W_S + it->infections_W_F + it->infections_B_S + it->infections_B_F) > it->max_sum_infections_combined)
                                                            {
                                                                it->max_sum_infections_combined = (it->infections_N_S + it->infections_N_F + it->infections_W_S + it->infections_W_F + it->infections_B_S + it->infections_B_F);
                                                                it->day_max_sum_infections_combined = disp_period_num + 1;
                                                            }


                                                            //Peak of hospitalizations of subjects with no immunity
                                                            if (it->hospitalized_N_S + it->hospitalized_N_F > it->max_sum_hospitalized_no_immunity)
                                                            {
                                                                it->max_sum_hospitalized_no_immunity = it->hospitalized_N_S + it->hospitalized_N_F;
                                                                it->day_max_sum_hospitalized_no_immunity = disp_period_num + 1;
                                                            }

                                                            //Peak of hospitalizations of subjects with waning immunity
                                                            if (it->hospitalized_W_S + it->hospitalized_W_F > it->max_sum_hospitalized_waning_immunity)
                                                            {
                                                                it->max_sum_hospitalized_waning_immunity = it->hospitalized_W_S + it->hospitalized_W_F;
                                                                it->day_max_sum_hospitalized_waning_immunity = disp_period_num + 1;
                                                            }

                                                            //Peak of hospitalizations of subjects with boosted immunity
                                                            if (it->hospitalized_B_S + it->hospitalized_B_F > it->max_sum_hospitalized_boosted_immunity)
                                                            {
                                                                it->max_sum_hospitalized_boosted_immunity = it->hospitalized_B_S + it->hospitalized_B_F;
                                                                it->day_max_sum_hospitalized_boosted_immunity = disp_period_num + 1;
                                                            }

                                                            //Peak of total hospitalizations
                                                            if (it->hospitalized_N_S + it->hospitalized_N_F + it->hospitalized_W_S + it->hospitalized_W_F + it->hospitalized_B_S + it->hospitalized_B_F > it->max_sum_hospitalized_combined)
                                                            {
                                                                it->max_sum_hospitalized_combined = it->hospitalized_N_S + it->hospitalized_N_F + it->hospitalized_W_S + it->hospitalized_W_F + it->hospitalized_B_S + it->hospitalized_B_F;
                                                                it->day_max_sum_hospitalized_combined = disp_period_num + 1;
                                                            }


                                                            //Total calculations:
                                                            //No immunity
                                                            it->cumul_infections_N_S = it->cumul_infections_N_S + it->infections_N_S;
                                                            it->cumul_infections_N_F = it->cumul_infections_N_F + it->infections_N_F;
                                                            it->cumul_infections_no_immunity = it->cumul_infections_no_immunity + it->infections_N_S + it->infections_N_F;
                                                            it->cumul_hospitalization_N_S = it->cumul_hospitalization_N_S + PI_N_S * it->current_symptomatic_N_S;
                                                            it->cumul_hospitalization_N_F = it->cumul_hospitalization_N_F + PI_N_F * it->current_symptomatic_N_F;
                                                            it->cumul_hospitalization_no_immunity = it->cumul_hospitalization_no_immunity + PI_N_S * it->current_symptomatic_N_S + PI_N_F * it->current_symptomatic_N_F;
                                                            it->cumul_deaths_N_S = it->cumul_deaths_N_S + DELTA_N_S * it->current_hospitalized_N_S;
                                                            it->cumul_deaths_N_F = it->cumul_deaths_N_F + DELTA_N_F * it->current_hospitalized_N_F;
                                                            it->cumul_deaths_no_immunity = it->cumul_deaths_no_immunity + DELTA_N_S * it->current_hospitalized_N_S + DELTA_N_F * it->current_hospitalized_N_F;

                                                            //Waning immunity
                                                            it->cumul_infections_W_S = it->cumul_infections_W_S + it->infections_W_S;
                                                            it->cumul_infections_W_F = it->cumul_infections_W_F + it->infections_W_F;
                                                            it->cumul_infections_waning_immunity = it->cumul_infections_waning_immunity + it->infections_W_S + it->infections_W_F;
                                                            it->cumul_hospitalization_W_S = it->cumul_hospitalization_W_S + PI_W_S * it->current_symptomatic_W_S;
                                                            it->cumul_hospitalization_W_F = it->cumul_hospitalization_W_F + PI_W_F * it->current_symptomatic_W_F;
                                                            it->cumul_hospitalization_waning_immunity = it->cumul_hospitalization_waning_immunity + PI_W_S * it->current_symptomatic_W_S + PI_W_F * it->current_symptomatic_W_F;
                                                            it->cumul_deaths_W_S = it->cumul_deaths_W_S + DELTA_W_S * it->current_hospitalized_W_S;
                                                            it->cumul_deaths_W_F = it->cumul_deaths_W_F + DELTA_W_F * it->current_hospitalized_W_F;
                                                            it->cumul_deaths_waning_immunity = it->cumul_deaths_waning_immunity + DELTA_W_S * it->current_hospitalized_W_S + DELTA_W_F * it->current_hospitalized_W_F;

                                                            //Boosted immunity
                                                            it->cumul_infections_B_S = it->cumul_infections_B_S + it->infections_B_S;
                                                            it->cumul_infections_B_F = it->cumul_infections_B_F + it->infections_B_F;
                                                            it->cumul_infections_boosted_immunity = it->cumul_infections_boosted_immunity + it->infections_B_S + it->infections_B_F;
                                                            it->cumul_hospitalization_B_S = it->cumul_hospitalization_B_S + PI_B_S * it->current_symptomatic_B_S;
                                                            it->cumul_hospitalization_B_F = it->cumul_hospitalization_B_F + PI_B_F * it->current_symptomatic_B_F;
                                                            it->cumul_hospitalization_boosted_immunity = it->cumul_hospitalization_boosted_immunity + PI_B_S * it->current_symptomatic_B_S + PI_B_F * it->current_symptomatic_B_F;
                                                            it->cumul_deaths_B_S = it->cumul_deaths_B_S + DELTA_B_S * it->current_hospitalized_B_S;
                                                            it->cumul_deaths_B_F = it->cumul_deaths_B_F + DELTA_B_F * it->current_hospitalized_B_F;
                                                            it->cumul_deaths_boosted_immunity = it->cumul_deaths_boosted_immunity + DELTA_B_S * it->current_hospitalized_B_S + DELTA_B_F * it->current_hospitalized_B_F;

                                                            //Total combined
                                                            it->cumul_infections_combined = it->cumul_infections_combined + it->infections_N_S + it->infections_N_F + it->infections_W_S + it->infections_W_F + it->infections_B_S + it->infections_B_F;
                                                            it->cumul_hospitalization_combined = it->cumul_hospitalization_combined + PI_N_S * it->current_symptomatic_N_S + PI_N_F * it->current_symptomatic_N_F + PI_W_S * it->current_symptomatic_W_S + PI_W_F * it->current_symptomatic_W_F + PI_B_S * it->current_symptomatic_B_S + PI_B_F * it->current_symptomatic_B_F;
                                                            it->cumul_deaths_combined = it->cumul_deaths_combined + DELTA_N_S * it->current_hospitalized_N_S + DELTA_N_F * it->current_hospitalized_N_F + DELTA_W_S * it->current_hospitalized_W_S + DELTA_W_F * it->current_hospitalized_W_F + DELTA_B_S * it->current_hospitalized_B_S + DELTA_B_F * it->current_hospitalized_B_F;



                                                            //Updates
                                                            it->previous_asymptomatic_infected_N_S = it->current_asymptomatic_N_S;
                                                            it->previous_uninfected_N_S = it->current_uninfected_N_S;
                                                            it->current_asymptomatic_N_S = it->asymptomatic_infected_N_S;
                                                            it->current_uninfected_N_S = it->uninfected_N_S;
                                                            it->current_exposed_asymptomatic_N_S = it->exposed_asymptomatic_N_S;
                                                            it->current_hospitalized_N_S = it->hospitalized_N_S;
                                                            it->current_TP_N_S = it->true_positive_N_S;
                                                            it->current_symptomatic_N_S = it->symptomatic_infected_N_S;
                                                            it->previous_RU_N_S = it->current_RU_N_S;
                                                            it->current_RU_N_S = it->recovered_unknown_N_S;
                                                            it->current_RK_N_S = it->recovered_known_N_S;


                                                            it->previous_asymptomatic_infected_W_S = it->current_asymptomatic_W_S;
                                                            it->previous_uninfected_W_S = it->current_uninfected_W_S;
                                                            it->current_asymptomatic_W_S = it->asymptomatic_infected_W_S;
                                                            it->current_uninfected_W_S = it->uninfected_W_S;
                                                            it->current_exposed_asymptomatic_W_S = it->exposed_asymptomatic_W_S;
                                                            it->current_hospitalized_W_S = it->hospitalized_W_S;
                                                            it->current_TP_W_S = it->true_positive_W_S;
                                                            it->current_symptomatic_W_S = it->symptomatic_infected_W_S;
                                                            it->previous_RU_W_S = it->current_RU_W_S;
                                                            it->current_RU_W_S = it->recovered_unknown_W_S;
                                                            it->current_RK_W_S = it->recovered_known_W_S;


                                                            it->previous_asymptomatic_infected_B_S = it->current_asymptomatic_B_S;
                                                            it->previous_uninfected_B_S = it->current_uninfected_B_S;
                                                            it->current_asymptomatic_B_S = it->asymptomatic_infected_B_S;
                                                            it->current_uninfected_B_S = it->uninfected_B_S;
                                                            it->current_exposed_asymptomatic_B_S = it->exposed_asymptomatic_B_S;
                                                            it->current_hospitalized_B_S = it->hospitalized_B_S;
                                                            it->current_TP_B_S = it->true_positive_B_S;
                                                            it->current_symptomatic_B_S = it->symptomatic_infected_B_S;
                                                            it->previous_RU_B_S = it->current_RU_B_S;
                                                            it->current_RU_B_S = it->recovered_unknown_B_S;
                                                            it->current_RK_B_S = it->recovered_known_B_S;



                                                            it->cumul_asymptomatic_N_F = it->cumul_asymptomatic_N_F + it->asymptomatic_infected_N_F;
                                                            it->previous_asymptomatic_infected_N_F = it->current_asymptomatic_N_F;
                                                            it->previous_uninfected_N_F = it->current_uninfected_N_F;
                                                            it->current_asymptomatic_N_F = it->asymptomatic_infected_N_F;
                                                            it->current_uninfected_N_F = it->uninfected_N_F;
                                                            it->current_exposed_asymptomatic_N_F = it->exposed_asymptomatic_N_F;
                                                            it->current_hospitalized_N_F = it->hospitalized_N_F;
                                                            it->current_TP_N_F = it->true_positive_N_F;
                                                            it->current_symptomatic_N_F = it->symptomatic_infected_N_F;
                                                            it->previous_RU_N_F = it->current_RU_N_F;
                                                            it->current_RU_N_F = it->recovered_unknown_N_F;
                                                            it->current_RK_N_F = it->recovered_known_N_F;


                                                            it->cumul_asymptomatic_W_F = it->cumul_asymptomatic_W_F + it->asymptomatic_infected_W_F;
                                                            it->previous_asymptomatic_infected_W_F = it->current_asymptomatic_W_F;
                                                            it->previous_uninfected_W_F = it->current_uninfected_W_F;
                                                            it->current_asymptomatic_W_F = it->asymptomatic_infected_W_F;
                                                            it->current_uninfected_W_F = it->uninfected_W_F;
                                                            it->current_exposed_asymptomatic_W_F = it->exposed_asymptomatic_W_F;
                                                            it->current_hospitalized_W_F = it->hospitalized_W_F;
                                                            it->current_TP_W_F = it->true_positive_W_F;
                                                            it->current_symptomatic_W_F = it->symptomatic_infected_W_F;
                                                            it->previous_RU_W_F = it->current_RU_W_F;
                                                            it->current_RU_W_F = it->recovered_unknown_W_F;
                                                            it->current_RK_W_F = it->recovered_known_W_F;


                                                            it->cumul_asymptomatic_B_F = it->cumul_asymptomatic_B_F + it->asymptomatic_infected_B_F;
                                                            it->previous_asymptomatic_infected_B_F = it->current_asymptomatic_B_F;
                                                            it->previous_uninfected_B_F = it->current_uninfected_B_F;
                                                            it->current_asymptomatic_B_F = it->asymptomatic_infected_B_F;
                                                            it->current_uninfected_B_F = it->uninfected_B_F;
                                                            it->current_exposed_asymptomatic_B_F = it->exposed_asymptomatic_B_F;
                                                            it->current_hospitalized_B_F = it->hospitalized_B_F;
                                                            it->current_TP_B_F = it->true_positive_B_F;
                                                            it->current_symptomatic_B_F = it->symptomatic_infected_B_F;
                                                            it->previous_RU_B_F = it->current_RU_B_F;
                                                            it->current_RU_B_F = it->recovered_unknown_B_F;
                                                            it->current_RK_B_F = it->recovered_known_B_F;




                                                            counter_for_periods = counter_for_periods + 1.0 / 3;


                                                            // }


                                                            if ((i == TOTAL_PERIODS_NUMBER - 1))    //|| (it->uninfected_N_S <= 0)|| (it->uninfected_N_F <= 0) || (it->uninfected_W_S <= 0) || (it->uninfected_W_F <= 0) || (it->uninfected_B_S <= 0) || (it->uninfected_B_F <= 0))
                                                            {

                                                                myfile_infections_table << "\t" << round(it->cumul_infections_N_S) << "\t" << round(it->cumul_infections_N_F) << "\t" << round(it->cumul_infections_no_immunity) << "\t" << round(it->cumul_infections_W_S) << "\t" << round(it->cumul_infections_W_F) << "\t" << round(it->cumul_infections_waning_immunity) << "\t" << round(it->cumul_infections_B_S) << "\t" << round(it->cumul_infections_B_F) << "\t" << round(it->cumul_infections_boosted_immunity) << "\t" << round(it->cumul_infections_combined);
                                                                myfile_infections_table << "\t" << round(it->cumul_hospitalization_N_S) << "\t" << round(it->cumul_hospitalization_N_F) << "\t" << round(it->cumul_hospitalization_no_immunity) << "\t" << round(it->cumul_hospitalization_W_S) << "\t" << round(it->cumul_hospitalization_W_F) << "\t" << round(it->cumul_hospitalization_waning_immunity) << "\t" << round(it->cumul_hospitalization_B_S) << "\t" << round(it->cumul_hospitalization_B_F) << "\t" << round(it->cumul_hospitalization_boosted_immunity) << "\t" << round(it->cumul_hospitalization_combined);
                                                                myfile_infections_table << "\t" << round(it->cumul_deaths_N_S) << "\t" << round(it->cumul_deaths_N_F) << "\t" << round(it->cumul_deaths_no_immunity) << "\t" << round(it->cumul_deaths_W_S) << "\t" << round(it->cumul_deaths_W_F) << "\t" << round(it->cumul_deaths_waning_immunity) << "\t" << round(it->cumul_deaths_B_S) << "\t" << round(it->cumul_deaths_B_F) << "\t" << round(it->cumul_deaths_boosted_immunity) << "\t" << round(it->cumul_deaths_combined);
                                                                myfile_infections_table << "\t" << round(it->max_sum_infections_no_immunity) << "\t" << round(it->day_max_sum_infections_no_immunity) << "\t" << round(it->max_sum_hospitalized_no_immunity) << "\t" << round(it->day_max_sum_hospitalized_no_immunity);
                                                                myfile_infections_table << "\t" << round(it->max_sum_infections_waning_immunity) << "\t" << round(it->day_max_sum_infections_waning_immunity) << "\t" << round(it->max_sum_hospitalized_waning_immunity) << "\t" << round(it->day_max_sum_hospitalized_waning_immunity);
                                                                myfile_infections_table << "\t" << round(it->max_sum_infections_boosted_immunity) << "\t" << round(it->day_max_sum_infections_boosted_immunity) << "\t" << round(it->max_sum_hospitalized_boosted_immunity) << "\t" << round(it->day_max_sum_hospitalized_boosted_immunity);
                                                                myfile_infections_table << "\t" << round(it->max_sum_infections_combined) << "\t" << round(it->day_max_sum_infections_combined) << "\t" << round(it->max_sum_hospitalized_combined) << "\t" << round(it->day_max_sum_hospitalized_combined) << endl;


                                                                it->average_screening_tests_used_N_S = it->cumul_screening_tests_used_N_S / 80;
                                                                it->average_screening_tests_used_N_F = it->cumul_screening_tests_used_N_F / 80;
                                                                it->average_screening_tests_used_W_S = it->cumul_screening_tests_used_W_S / 80;
                                                                it->average_screening_tests_used_W_F = it->cumul_screening_tests_used_W_F / 80;
                                                                it->average_screening_tests_used_B_S = it->cumul_screening_tests_used_B_S / 80;
                                                                it->average_screening_tests_used_B_F = it->cumul_screening_tests_used_B_F / 80;

                                                                it->average_screening_tests_used_no_immunity = it->cumul_screening_tests_used_no_immunity / 80;
                                                                it->average_screening_tests_used_waning_immunity = it->cumul_screening_tests_used_waning_immunity / 80;
                                                                it->average_screening_tests_used_boosted_immunity = it->cumul_screening_tests_used_boosted_immunity / 80;
                                                                it->average_screening_tests_used_combined = it->cumul_screening_tests_used_combined / 80;



                                                                if (k == 0 && e == 0 && a == 0 && p == 0 && q == 0 && w == 0 && b == 0 ) //&& q_f == 0 && w_f == 0 && b_f == 0)   uncomment if we differentiate between faculty and students
                                                                {
                                                                    number_of_infections_no_screening = it->cumul_infections_combined;
                                                                    peak_of_infections_no_screening = it->max_sum_infections_combined;
                                                                }

                                                                else
                                                                {
                                                                    it->ratio_per_100_tests = 100 * (number_of_infections_no_screening - it->cumul_infections_combined) / (it->average_screening_tests_used_combined * 80);
                                                                    it->ratio_of_peak_per_100_tests = 100 * (peak_of_infections_no_screening - it->max_sum_infections_combined) / (it->average_screening_tests_used_combined * 80);
                                                                }

                                                                if (it->ratio_per_100_tests > max_ratio_total_infections_no_screening_for_unvaccinated_students && TAU_N_S == 0)
                                                                {
                                                                    max_ratio_total_infections_no_screening_for_unvaccinated_students = it->ratio_per_100_tests;
                                                                    tau_array_for_max_ratio_total_infections_no_screening_for_unvaccinated_students[0] = TAU_W_S;
                                                                    tau_array_for_max_ratio_total_infections_no_screening_for_unvaccinated_students[1] = TAU_B_S;
                                                                    tau_array_for_max_ratio_total_infections_no_screening_for_unvaccinated_students[2] = TAU_N_F;
                                                                    tau_array_for_max_ratio_total_infections_no_screening_for_unvaccinated_students[3] = TAU_W_F;
                                                                    tau_array_for_max_ratio_total_infections_no_screening_for_unvaccinated_students[4] = TAU_B_F;

                                                                }

                                                                if (it->ratio_of_peak_per_100_tests > max_ratio_peak_infections_no_screening_for_unvaccinated_students && TAU_N_S == 0)
                                                                {
                                                                    max_ratio_peak_infections_no_screening_for_unvaccinated_students = it->ratio_of_peak_per_100_tests;
                                                                    tau_array_for_max_ratio_peak_infections_no_screening_for_unvaccinated_students[0] = TAU_W_S;
                                                                    tau_array_for_max_ratio_peak_infections_no_screening_for_unvaccinated_students[1] = TAU_B_S;
                                                                    tau_array_for_max_ratio_peak_infections_no_screening_for_unvaccinated_students[2] = TAU_N_F;
                                                                    tau_array_for_max_ratio_peak_infections_no_screening_for_unvaccinated_students[3] = TAU_W_F;
                                                                    tau_array_for_max_ratio_peak_infections_no_screening_for_unvaccinated_students[4] = TAU_B_F;

                                                                }


                                                                if (it->ratio_per_100_tests > max_ratio_total_infections_14d_for_unvaccinated_students && TAU_N_S == 1.0 / (3 * 14.0))
                                                                {
                                                                    max_ratio_total_infections_14d_for_unvaccinated_students = it->ratio_per_100_tests;
                                                                    tau_array_for_max_ratio_total_infections_14d_for_unvaccinated_students[0] = TAU_W_S;
                                                                    tau_array_for_max_ratio_total_infections_14d_for_unvaccinated_students[1] = TAU_B_S;
                                                                    tau_array_for_max_ratio_total_infections_14d_for_unvaccinated_students[2] = TAU_N_F;
                                                                    tau_array_for_max_ratio_total_infections_14d_for_unvaccinated_students[3] = TAU_W_F;
                                                                    tau_array_for_max_ratio_total_infections_14d_for_unvaccinated_students[4] = TAU_B_F;

                                                                }

                                                                if (it->ratio_of_peak_per_100_tests > max_ratio_peak_infections_14d_for_unvaccinated_students && TAU_N_S == 1.0 / (3 * 14.0))
                                                                {
                                                                    max_ratio_peak_infections_14d_for_unvaccinated_students = it->ratio_of_peak_per_100_tests;
                                                                    tau_array_for_max_ratio_peak_infections_14d_for_unvaccinated_students[0] = TAU_W_S;
                                                                    tau_array_for_max_ratio_peak_infections_14d_for_unvaccinated_students[1] = TAU_B_S;
                                                                    tau_array_for_max_ratio_peak_infections_14d_for_unvaccinated_students[2] = TAU_N_F;
                                                                    tau_array_for_max_ratio_peak_infections_14d_for_unvaccinated_students[3] = TAU_W_F;
                                                                    tau_array_for_max_ratio_peak_infections_14d_for_unvaccinated_students[4] = TAU_B_F;

                                                                }

                                                                if (it->ratio_per_100_tests > max_ratio_total_infections_7d_for_unvaccinated_students && TAU_N_S == 1.0 / (3 * 7.0))
                                                                {
                                                                    max_ratio_total_infections_7d_for_unvaccinated_students = it->ratio_per_100_tests;
                                                                    tau_array_for_max_ratio_total_infections_7d_for_unvaccinated_students[0] = TAU_W_S;
                                                                    tau_array_for_max_ratio_total_infections_7d_for_unvaccinated_students[1] = TAU_B_S;
                                                                    tau_array_for_max_ratio_total_infections_7d_for_unvaccinated_students[2] = TAU_N_F;
                                                                    tau_array_for_max_ratio_total_infections_7d_for_unvaccinated_students[3] = TAU_W_F;
                                                                    tau_array_for_max_ratio_total_infections_7d_for_unvaccinated_students[4] = TAU_B_F;

                                                                }

                                                                if (it->ratio_of_peak_per_100_tests > max_ratio_peak_infections_7d_for_unvaccinated_students && TAU_N_S == 1.0 / (3 * 7.0))
                                                                {
                                                                    max_ratio_peak_infections_7d_for_unvaccinated_students = it->ratio_of_peak_per_100_tests;
                                                                    tau_array_for_max_ratio_peak_infections_7d_for_unvaccinated_students[0] = TAU_W_S;
                                                                    tau_array_for_max_ratio_peak_infections_7d_for_unvaccinated_students[1] = TAU_B_S;
                                                                    tau_array_for_max_ratio_peak_infections_7d_for_unvaccinated_students[2] = TAU_N_F;
                                                                    tau_array_for_max_ratio_peak_infections_7d_for_unvaccinated_students[3] = TAU_W_F;
                                                                    tau_array_for_max_ratio_peak_infections_7d_for_unvaccinated_students[4] = TAU_B_F;

                                                                }

                                                                if (it->ratio_per_100_tests > max_ratio_total_infections_3d_for_unvaccinated_students && TAU_N_S == 1.0 / (3 * 3.0))
                                                                {
                                                                    max_ratio_total_infections_3d_for_unvaccinated_students = it->ratio_per_100_tests;
                                                                    tau_array_for_max_ratio_total_infections_3d_for_unvaccinated_students[0] = TAU_W_S;
                                                                    tau_array_for_max_ratio_total_infections_3d_for_unvaccinated_students[1] = TAU_B_S;
                                                                    tau_array_for_max_ratio_total_infections_3d_for_unvaccinated_students[2] = TAU_N_F;
                                                                    tau_array_for_max_ratio_total_infections_3d_for_unvaccinated_students[3] = TAU_W_F;
                                                                    tau_array_for_max_ratio_total_infections_3d_for_unvaccinated_students[4] = TAU_B_F;

                                                                }

                                                                if (it->ratio_of_peak_per_100_tests > max_ratio_peak_infections_3d_for_unvaccinated_students && TAU_N_S == 1.0 / (3 * 3.0))
                                                                {
                                                                    max_ratio_peak_infections_3d_for_unvaccinated_students = it->ratio_of_peak_per_100_tests;
                                                                    tau_array_for_max_ratio_peak_infections_3d_for_unvaccinated_students[0] = TAU_W_S;
                                                                    tau_array_for_max_ratio_peak_infections_3d_for_unvaccinated_students[1] = TAU_B_S;
                                                                    tau_array_for_max_ratio_peak_infections_3d_for_unvaccinated_students[2] = TAU_N_F;
                                                                    tau_array_for_max_ratio_peak_infections_3d_for_unvaccinated_students[3] = TAU_W_F;
                                                                    tau_array_for_max_ratio_peak_infections_3d_for_unvaccinated_students[4] = TAU_B_F;

                                                                }

                                                                if (it->ratio_per_100_tests > max_ratio_total_infections_2d_for_unvaccinated_students && TAU_N_S == 1.0 / (3 * 2.0))
                                                                {
                                                                    max_ratio_total_infections_2d_for_unvaccinated_students = it->ratio_per_100_tests;
                                                                    tau_array_for_max_ratio_total_infections_2d_for_unvaccinated_students[0] = TAU_W_S;
                                                                    tau_array_for_max_ratio_total_infections_2d_for_unvaccinated_students[1] = TAU_B_S;
                                                                    tau_array_for_max_ratio_total_infections_2d_for_unvaccinated_students[2] = TAU_N_F;
                                                                    tau_array_for_max_ratio_total_infections_2d_for_unvaccinated_students[3] = TAU_W_F;
                                                                    tau_array_for_max_ratio_total_infections_2d_for_unvaccinated_students[4] = TAU_B_F;

                                                                }

                                                                if (it->ratio_of_peak_per_100_tests > max_ratio_peak_infections_2d_for_unvaccinated_students && TAU_N_S == 1.0 / (3 * 2.0))
                                                                {
                                                                    max_ratio_peak_infections_2d_for_unvaccinated_students = it->ratio_of_peak_per_100_tests;
                                                                    tau_array_for_max_ratio_peak_infections_2d_for_unvaccinated_students[0] = TAU_W_S;
                                                                    tau_array_for_max_ratio_peak_infections_2d_for_unvaccinated_students[1] = TAU_B_S;
                                                                    tau_array_for_max_ratio_peak_infections_2d_for_unvaccinated_students[2] = TAU_N_F;
                                                                    tau_array_for_max_ratio_peak_infections_2d_for_unvaccinated_students[3] = TAU_W_F;
                                                                    tau_array_for_max_ratio_peak_infections_2d_for_unvaccinated_students[4] = TAU_B_F;

                                                                }

                                                                if (it->ratio_per_100_tests > max_ratio_total_infections_1d_for_unvaccinated_students && TAU_N_S == 1.0 / (3 * 1.0))
                                                                {
                                                                    max_ratio_total_infections_1d_for_unvaccinated_students = it->ratio_per_100_tests;
                                                                    tau_array_for_max_ratio_total_infections_1d_for_unvaccinated_students[0] = TAU_W_S;
                                                                    tau_array_for_max_ratio_total_infections_1d_for_unvaccinated_students[1] = TAU_B_S;
                                                                    tau_array_for_max_ratio_total_infections_1d_for_unvaccinated_students[2] = TAU_N_F;
                                                                    tau_array_for_max_ratio_total_infections_1d_for_unvaccinated_students[3] = TAU_W_F;
                                                                    tau_array_for_max_ratio_total_infections_1d_for_unvaccinated_students[4] = TAU_B_F;

                                                                }

                                                                if (it->ratio_of_peak_per_100_tests > max_ratio_peak_infections_1d_for_unvaccinated_students && TAU_N_S == 1.0 / (3 * 1.0))
                                                                {
                                                                    max_ratio_peak_infections_1d_for_unvaccinated_students = it->ratio_of_peak_per_100_tests;
                                                                    tau_array_for_max_ratio_peak_infections_1d_for_unvaccinated_students[0] = TAU_W_S;
                                                                    tau_array_for_max_ratio_peak_infections_1d_for_unvaccinated_students[1] = TAU_B_S;
                                                                    tau_array_for_max_ratio_peak_infections_1d_for_unvaccinated_students[2] = TAU_N_F;
                                                                    tau_array_for_max_ratio_peak_infections_1d_for_unvaccinated_students[3] = TAU_W_F;
                                                                    tau_array_for_max_ratio_peak_infections_1d_for_unvaccinated_students[4] = TAU_B_F;

                                                                }


                                                                myfile_screening_table << "\t" << round(it->average_screening_tests_used_N_S) << "\t" << round(it->average_screening_tests_used_N_F) << "\t" << round(it->average_screening_tests_used_no_immunity) << "\t" << round(it->average_screening_tests_used_W_S) << "\t" << round(it->average_screening_tests_used_W_F) << "\t" << round(it->average_screening_tests_used_waning_immunity) << "\t" << round(it->average_screening_tests_used_B_S) << "\t" << round(it->average_screening_tests_used_B_F) << "\t" << round(it->average_screening_tests_used_boosted_immunity) << "\t" << round(it->average_screening_tests_used_combined) << endl;

                                                                if (TAU_N_S == TAU_N_F && TAU_W_S == TAU_W_F && TAU_B_S == TAU_B_F && ((TAU_W_S == TAU_N_S) || (TAU_W_S == 0)) && ((TAU_B_S == TAU_N_S) || (TAU_B_S == 0)))
                                                                {
                                                                    //customized_scenarios_filtered << "\t" << round(it->cumul_infections_combined) << "\t" << round(it->max_sum_infections_combined) << "\t" << round(it->average_screening_tests_used_combined) << "\t" << it->ratio_per_100_tests << "\t" << it->ratio_of_peak_per_100_tests << endl;
                                                                    customized_scenarios_filtered << "\t" << it->ratio_per_100_tests << "\t" << it->ratio_of_peak_per_100_tests << endl;

                                                                }

                                                                loop_index = i + 1;


                                                            }


                                                        }


                                                        if (i >= disp_period_num * REPORTING_INTERVAL) // increase disp_period_num so that we do not report until the next REPORTING_INTERVAL
                                                        {
                                                            disp_period_num++;
                                                        }



                                                    }

                                                }
                                            }


                                        }
                                    }
                                }


                            }

                            //I will plot some results sequentially 

                            //////////////////////////////////////////
                            /////////////////////////////// total ////////////////////  
                            /////////////////////////////////////////
                            best_scenarios_total_infections << OMEGA * 100 << "%" << "\t" << U_N_F_0 << "\t" << U_N_S_0 << "\t" << U_W_F_0 << "\t" << U_W_S_0 << "\t" << U_B_F_0 << "\t" << U_B_S_0 << "\t" << ETA << "\t" << GAMMA;
                            if (LAMBDA == 0)
                            {
                                best_scenarios_total_infections << "\t" << 0;
                            }
                            else
                            {
                                best_scenarios_total_infections << "\t" << 1.0 / (3 * LAMBDA * 7);
                            }


                            //NO SCREENING FOR UNVACCINATED STUDENTS
                            best_scenarios_total_infections << "\t" << "N/A";   //N_S no screening

                            if (tau_array_for_max_ratio_total_infections_no_screening_for_unvaccinated_students[0] == 0)
                            {
                                best_scenarios_total_infections << "\t" << "N/A";


                            }
                            else {
                                best_scenarios_total_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_total_infections_no_screening_for_unvaccinated_students[0]) << "d";

                            }

                            if (tau_array_for_max_ratio_total_infections_no_screening_for_unvaccinated_students[1] == 0) {
                                best_scenarios_total_infections << "\t" << "N/A";

                            }
                            else
                            {
                                best_scenarios_total_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_total_infections_no_screening_for_unvaccinated_students[1]) << "d";

                            }

                            if (tau_array_for_max_ratio_total_infections_no_screening_for_unvaccinated_students[2] == 0) {
                                best_scenarios_total_infections << "\t" << "N/A";

                            }
                            else {
                                best_scenarios_total_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_total_infections_no_screening_for_unvaccinated_students[2]) << "d";

                            }
                            if (tau_array_for_max_ratio_total_infections_no_screening_for_unvaccinated_students[3] == 0)
                            {
                                best_scenarios_total_infections << "\t" << "N/A";

                            }
                            else
                            {
                                best_scenarios_total_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_total_infections_no_screening_for_unvaccinated_students[3]) << "d";

                            }
                            if (tau_array_for_max_ratio_total_infections_no_screening_for_unvaccinated_students[4] == 0) {
                                best_scenarios_total_infections << "\t" << "N/A";
                            }
                            else
                            {
                                best_scenarios_total_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_total_infections_no_screening_for_unvaccinated_students[4]) << "d";

                            }
                            best_scenarios_total_infections << "\t" << max_ratio_total_infections_no_screening_for_unvaccinated_students << endl;

                            /////////////////////////////   Sreening every 14 days FOR UNVACCINATED STUDENTS
                            best_scenarios_total_infections << OMEGA * 100 << "%" << "\t" << U_N_F_0 << "\t" << U_N_S_0 << "\t" << U_W_F_0 << "\t" << U_W_S_0 << "\t" << U_B_F_0 << "\t" << U_B_S_0 << "\t" << ETA << "\t" << GAMMA;
                            if (LAMBDA == 0)
                            {
                                best_scenarios_total_infections << "\t" << 0;
                            }
                            else
                            {
                                best_scenarios_total_infections << "\t" << 1.0 / (3 * LAMBDA * 7);
                            }

                            best_scenarios_total_infections << "\t" << "14d";   //N_S 14d

                            if (tau_array_for_max_ratio_total_infections_14d_for_unvaccinated_students[0] == 0)
                            {
                                best_scenarios_total_infections << "\t" << "N/A";

                            }
                            else {
                                best_scenarios_total_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_total_infections_14d_for_unvaccinated_students[0]) << "d";

                            }

                            if (tau_array_for_max_ratio_total_infections_14d_for_unvaccinated_students[1] == 0) {
                                best_scenarios_total_infections << "\t" << "N/A";

                            }
                            else
                            {
                                best_scenarios_total_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_total_infections_14d_for_unvaccinated_students[1]) << "d";

                            }

                            if (tau_array_for_max_ratio_total_infections_14d_for_unvaccinated_students[2] == 0) {
                                best_scenarios_total_infections << "\t" << "N/A";

                            }
                            else {
                                best_scenarios_total_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_total_infections_14d_for_unvaccinated_students[2]) << "d";

                            }
                            if (tau_array_for_max_ratio_total_infections_14d_for_unvaccinated_students[3] == 0)
                            {
                                best_scenarios_total_infections << "\t" << "N/A";

                            }
                            else
                            {
                                best_scenarios_total_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_total_infections_14d_for_unvaccinated_students[3]) << "d";

                            }
                            if (tau_array_for_max_ratio_total_infections_14d_for_unvaccinated_students[4] == 0) {
                                best_scenarios_total_infections << "\t" << "N/A";
                            }
                            else
                            {
                                best_scenarios_total_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_total_infections_14d_for_unvaccinated_students[4]) << "d";

                            }
                            best_scenarios_total_infections << "\t" << max_ratio_total_infections_14d_for_unvaccinated_students << endl;

                            /////////////////////////////   Sreening every 7 days FOR UNVACCINATED STUDENTS
                            best_scenarios_total_infections << OMEGA * 100 << "%" << "\t" << U_N_F_0 << "\t" << U_N_S_0 << "\t" << U_W_F_0 << "\t" << U_W_S_0 << "\t" << U_B_F_0 << "\t" << U_B_S_0 << "\t" << ETA << "\t" << GAMMA;
                            if (LAMBDA == 0)
                            {
                                best_scenarios_total_infections << "\t" << 0;
                            }
                            else
                            {
                                best_scenarios_total_infections << "\t" << 1.0 / (3 * LAMBDA * 7);
                            }

                            best_scenarios_total_infections << "\t" << "7d";   //N_S 7d

                            if (tau_array_for_max_ratio_total_infections_7d_for_unvaccinated_students[0] == 0)
                            {
                                best_scenarios_total_infections << "\t" << "N/A";

                            }
                            else {
                                best_scenarios_total_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_total_infections_7d_for_unvaccinated_students[0]) << "d";

                            }

                            if (tau_array_for_max_ratio_total_infections_7d_for_unvaccinated_students[1] == 0) {
                                best_scenarios_total_infections << "\t" << "N/A";

                            }
                            else
                            {
                                best_scenarios_total_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_total_infections_7d_for_unvaccinated_students[1]) << "d";

                            }

                            if (tau_array_for_max_ratio_total_infections_7d_for_unvaccinated_students[2] == 0) {
                                best_scenarios_total_infections << "\t" << "N/A";

                            }
                            else {
                                best_scenarios_total_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_total_infections_7d_for_unvaccinated_students[2]) << "d";

                            }
                            if (tau_array_for_max_ratio_total_infections_7d_for_unvaccinated_students[3] == 0)
                            {
                                best_scenarios_total_infections << "\t" << "N/A";

                            }
                            else
                            {
                                best_scenarios_total_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_total_infections_7d_for_unvaccinated_students[3]) << "d";

                            }
                            if (tau_array_for_max_ratio_total_infections_7d_for_unvaccinated_students[4] == 0) {
                                best_scenarios_total_infections << "\t" << "N/A";
                            }
                            else
                            {
                                best_scenarios_total_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_total_infections_7d_for_unvaccinated_students[4]) << "d";

                            }
                            best_scenarios_total_infections << "\t" << max_ratio_total_infections_7d_for_unvaccinated_students << endl;

                            /////////////////////////////   Sreening every 3 days FOR UNVACCINATED STUDENTS
                            best_scenarios_total_infections << OMEGA * 100 << "%" << "\t" << U_N_F_0 << "\t" << U_N_S_0 << "\t" << U_W_F_0 << "\t" << U_W_S_0 << "\t" << U_B_F_0 << "\t" << U_B_S_0 << "\t" << ETA << "\t" << GAMMA;
                            if (LAMBDA == 0)
                            {
                                best_scenarios_total_infections << "\t" << 0;
                            }
                            else
                            {
                                best_scenarios_total_infections << "\t" << 1.0 / (3 * LAMBDA * 7);
                            }

                            best_scenarios_total_infections << "\t" << "3d";   //N_S 3d

                            if (tau_array_for_max_ratio_total_infections_3d_for_unvaccinated_students[0] == 0)
                            {
                                best_scenarios_total_infections << "\t" << "N/A";

                            }
                            else {
                                best_scenarios_total_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_total_infections_3d_for_unvaccinated_students[0]) << "d";

                            }

                            if (tau_array_for_max_ratio_total_infections_3d_for_unvaccinated_students[1] == 0) {
                                best_scenarios_total_infections << "\t" << "N/A";

                            }
                            else
                            {
                                best_scenarios_total_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_total_infections_3d_for_unvaccinated_students[1]) << "d";

                            }

                            if (tau_array_for_max_ratio_total_infections_3d_for_unvaccinated_students[2] == 0) {
                                best_scenarios_total_infections << "\t" << "N/A";

                            }
                            else {
                                best_scenarios_total_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_total_infections_3d_for_unvaccinated_students[2]) << "d";

                            }
                            if (tau_array_for_max_ratio_total_infections_3d_for_unvaccinated_students[3] == 0)
                            {
                                best_scenarios_total_infections << "\t" << "N/A";

                            }
                            else
                            {
                                best_scenarios_total_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_total_infections_3d_for_unvaccinated_students[3]) << "d";

                            }
                            if (tau_array_for_max_ratio_total_infections_3d_for_unvaccinated_students[4] == 0) {
                                best_scenarios_total_infections << "\t" << "N/A";
                            }
                            else
                            {
                                best_scenarios_total_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_total_infections_3d_for_unvaccinated_students[4]) << "d";

                            }
                            best_scenarios_total_infections << "\t" << max_ratio_total_infections_3d_for_unvaccinated_students << endl;

                            /////////////////////////////   Sreening every 2 days FOR UNVACCINATED STUDENTS
                            best_scenarios_total_infections << OMEGA * 100 << "%" << "\t" << U_N_F_0 << "\t" << U_N_S_0 << "\t" << U_W_F_0 << "\t" << U_W_S_0 << "\t" << U_B_F_0 << "\t" << U_B_S_0 << "\t" << ETA << "\t" << GAMMA;
                            if (LAMBDA == 0)
                            {
                                best_scenarios_total_infections << "\t" << 0;
                            }
                            else
                            {
                                best_scenarios_total_infections << "\t" << 1.0 / (3 * LAMBDA * 7);
                            }

                            best_scenarios_total_infections << "\t" << "2d";   //N_S 2d

                            if (tau_array_for_max_ratio_total_infections_2d_for_unvaccinated_students[0] == 0)
                            {
                                best_scenarios_total_infections << "\t" << "N/A";

                            }
                            else {
                                best_scenarios_total_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_total_infections_2d_for_unvaccinated_students[0]) << "d";

                            }

                            if (tau_array_for_max_ratio_total_infections_2d_for_unvaccinated_students[1] == 0) {
                                best_scenarios_total_infections << "\t" << "N/A";

                            }
                            else
                            {
                                best_scenarios_total_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_total_infections_2d_for_unvaccinated_students[1]) << "d";

                            }

                            if (tau_array_for_max_ratio_total_infections_2d_for_unvaccinated_students[2] == 0) {
                                best_scenarios_total_infections << "\t" << "N/A";

                            }
                            else {
                                best_scenarios_total_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_total_infections_2d_for_unvaccinated_students[2]) << "d";

                            }
                            if (tau_array_for_max_ratio_total_infections_2d_for_unvaccinated_students[3] == 0)
                            {
                                best_scenarios_total_infections << "\t" << "N/A";

                            }
                            else
                            {
                                best_scenarios_total_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_total_infections_2d_for_unvaccinated_students[3]) << "d";

                            }
                            if (tau_array_for_max_ratio_total_infections_2d_for_unvaccinated_students[4] == 0) {
                                best_scenarios_total_infections << "\t" << "N/A";
                            }
                            else
                            {
                                best_scenarios_total_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_total_infections_2d_for_unvaccinated_students[4]) << "d";

                            }
                            best_scenarios_total_infections << "\t" << max_ratio_total_infections_2d_for_unvaccinated_students << endl;

                            /////////////////////////////   Sreening every 1 days FOR UNVACCINATED STUDENTS
                            best_scenarios_total_infections << OMEGA * 100 << "%" << "\t" << U_N_F_0 << "\t" << U_N_S_0 << "\t" << U_W_F_0 << "\t" << U_W_S_0 << "\t" << U_B_F_0 << "\t" << U_B_S_0 << "\t" << ETA << "\t" << GAMMA;
                            if (LAMBDA == 0)
                            {
                                best_scenarios_total_infections << "\t" << 0;
                            }
                            else
                            {
                                best_scenarios_total_infections << "\t" << 1.0 / (3 * LAMBDA * 7);
                            }

                            best_scenarios_total_infections << "\t" << "1d";   //N_S 1d

                            if (tau_array_for_max_ratio_total_infections_1d_for_unvaccinated_students[0] == 0)
                            {
                                best_scenarios_total_infections << "\t" << "N/A";

                            }
                            else {
                                best_scenarios_total_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_total_infections_1d_for_unvaccinated_students[0]) << "d";

                            }

                            if (tau_array_for_max_ratio_total_infections_1d_for_unvaccinated_students[1] == 0) {
                                best_scenarios_total_infections << "\t" << "N/A";

                            }
                            else
                            {
                                best_scenarios_total_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_total_infections_1d_for_unvaccinated_students[1]) << "d";

                            }

                            if (tau_array_for_max_ratio_total_infections_1d_for_unvaccinated_students[2] == 0) {
                                best_scenarios_total_infections << "\t" << "N/A";

                            }
                            else {
                                best_scenarios_total_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_total_infections_1d_for_unvaccinated_students[2]) << "d";

                            }
                            if (tau_array_for_max_ratio_total_infections_1d_for_unvaccinated_students[3] == 0)
                            {
                                best_scenarios_total_infections << "\t" << "N/A";

                            }
                            else
                            {
                                best_scenarios_total_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_total_infections_1d_for_unvaccinated_students[3]) << "d";

                            }
                            if (tau_array_for_max_ratio_total_infections_1d_for_unvaccinated_students[4] == 0) {
                                best_scenarios_total_infections << "\t" << "N/A";
                            }
                            else
                            {
                                best_scenarios_total_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_total_infections_1d_for_unvaccinated_students[4]) << "d";

                            }

                            best_scenarios_total_infections << "\t" << max_ratio_total_infections_1d_for_unvaccinated_students << endl;



                            //////////////////////////////////////////////
                            /////////////////////////////// peak ////////////////////  
                            ///////////////////////////////////////////////
                            best_scenarios_peak_infections << OMEGA * 100 << "%" << "\t" << U_N_F_0 << "\t" << U_N_S_0 << "\t" << U_W_F_0 << "\t" << U_W_S_0 << "\t" << U_B_F_0 << "\t" << U_B_S_0 << "\t" << ETA << "\t" << GAMMA;
                            if (LAMBDA == 0)
                            {
                                best_scenarios_peak_infections << "\t" << 0;
                            }
                            else
                            {
                                best_scenarios_peak_infections << "\t" << 1.0 / (3 * LAMBDA * 7);
                            }


                            //NO SCREENING FOR UNVACCINATED STUDENTS
                            best_scenarios_peak_infections << "\t" << "N/A";   //N_S no screening

                            if (tau_array_for_max_ratio_peak_infections_no_screening_for_unvaccinated_students[0] == 0)
                            {
                                best_scenarios_peak_infections << "\t" << "N/A";

                            }
                            else {
                                best_scenarios_peak_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_peak_infections_no_screening_for_unvaccinated_students[0]) << "d";

                            }

                            if (tau_array_for_max_ratio_peak_infections_no_screening_for_unvaccinated_students[1] == 0) {
                                best_scenarios_peak_infections << "\t" << "N/A";

                            }
                            else
                            {
                                best_scenarios_peak_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_peak_infections_no_screening_for_unvaccinated_students[1]) << "d";

                            }

                            if (tau_array_for_max_ratio_peak_infections_no_screening_for_unvaccinated_students[2] == 0) {
                                best_scenarios_peak_infections << "\t" << "N/A";

                            }
                            else {
                                best_scenarios_peak_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_peak_infections_no_screening_for_unvaccinated_students[2]) << "d";

                            }
                            if (tau_array_for_max_ratio_peak_infections_no_screening_for_unvaccinated_students[3] == 0)
                            {
                                best_scenarios_peak_infections << "\t" << "N/A";

                            }
                            else
                            {
                                best_scenarios_peak_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_peak_infections_no_screening_for_unvaccinated_students[3]) << "d";

                            }
                            if (tau_array_for_max_ratio_peak_infections_no_screening_for_unvaccinated_students[4] == 0) {
                                best_scenarios_peak_infections << "\t" << "N/A";
                            }
                            else
                            {
                                best_scenarios_peak_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_peak_infections_no_screening_for_unvaccinated_students[4]) << "d";

                            }
                            best_scenarios_peak_infections << "\t" << max_ratio_peak_infections_no_screening_for_unvaccinated_students << endl;

                            /////////////////////////////   Sreening every 14 days FOR UNVACCINATED STUDENTS
                            best_scenarios_peak_infections << OMEGA * 100 << "%" << "\t" << U_N_F_0 << "\t" << U_N_S_0 << "\t" << U_W_F_0 << "\t" << U_W_S_0 << "\t" << U_B_F_0 << "\t" << U_B_S_0 << "\t" << ETA << "\t" << GAMMA;
                            if (LAMBDA == 0)
                            {
                                best_scenarios_peak_infections << "\t" << 0;
                            }
                            else
                            {
                                best_scenarios_peak_infections << "\t" << 1.0 / (3 * LAMBDA * 7);
                            }

                            best_scenarios_peak_infections << "\t" << "14d";   //N_S 14d

                            if (tau_array_for_max_ratio_peak_infections_14d_for_unvaccinated_students[0] == 0)
                            {
                                best_scenarios_peak_infections << "\t" << "N/A";

                            }
                            else {
                                best_scenarios_peak_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_peak_infections_14d_for_unvaccinated_students[0]) << "d";

                            }

                            if (tau_array_for_max_ratio_peak_infections_14d_for_unvaccinated_students[1] == 0) {
                                best_scenarios_peak_infections << "\t" << "N/A";

                            }
                            else
                            {
                                best_scenarios_peak_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_peak_infections_14d_for_unvaccinated_students[1]) << "d";

                            }

                            if (tau_array_for_max_ratio_peak_infections_14d_for_unvaccinated_students[2] == 0) {
                                best_scenarios_peak_infections << "\t" << "N/A";

                            }
                            else {
                                best_scenarios_peak_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_peak_infections_14d_for_unvaccinated_students[2]) << "d";

                            }
                            if (tau_array_for_max_ratio_peak_infections_14d_for_unvaccinated_students[3] == 0)
                            {
                                best_scenarios_peak_infections << "\t" << "N/A";

                            }
                            else
                            {
                                best_scenarios_peak_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_peak_infections_14d_for_unvaccinated_students[3]) << "d";

                            }
                            if (tau_array_for_max_ratio_peak_infections_14d_for_unvaccinated_students[4] == 0) {
                                best_scenarios_peak_infections << "\t" << "N/A";
                            }
                            else
                            {
                                best_scenarios_peak_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_peak_infections_14d_for_unvaccinated_students[4]) << "d";

                            }
                            best_scenarios_peak_infections << "\t" << max_ratio_peak_infections_14d_for_unvaccinated_students << endl;

                            /////////////////////////////   Sreening every 7 days FOR UNVACCINATED STUDENTS
                            best_scenarios_peak_infections << OMEGA * 100 << "%" << "\t" << U_N_F_0 << "\t" << U_N_S_0 << "\t" << U_W_F_0 << "\t" << U_W_S_0 << "\t" << U_B_F_0 << "\t" << U_B_S_0 << "\t" << ETA << "\t" << GAMMA;
                            if (LAMBDA == 0)
                            {
                                best_scenarios_peak_infections << "\t" << 0;
                            }
                            else
                            {
                                best_scenarios_peak_infections << "\t" << 1.0 / (3 * LAMBDA * 7);
                            }

                            best_scenarios_peak_infections << "\t" << "7d";   //N_S 7d

                            if (tau_array_for_max_ratio_peak_infections_7d_for_unvaccinated_students[0] == 0)
                            {
                                best_scenarios_peak_infections << "\t" << "N/A";

                            }
                            else {
                                best_scenarios_peak_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_peak_infections_7d_for_unvaccinated_students[0]) << "d";

                            }

                            if (tau_array_for_max_ratio_peak_infections_7d_for_unvaccinated_students[1] == 0) {
                                best_scenarios_peak_infections << "\t" << "N/A";

                            }
                            else
                            {
                                best_scenarios_peak_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_peak_infections_7d_for_unvaccinated_students[1]) << "d";

                            }

                            if (tau_array_for_max_ratio_peak_infections_7d_for_unvaccinated_students[2] == 0) {
                                best_scenarios_peak_infections << "\t" << "N/A";

                            }
                            else {
                                best_scenarios_peak_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_peak_infections_7d_for_unvaccinated_students[2]) << "d";

                            }
                            if (tau_array_for_max_ratio_peak_infections_7d_for_unvaccinated_students[3] == 0)
                            {
                                best_scenarios_peak_infections << "\t" << "N/A";

                            }
                            else
                            {
                                best_scenarios_peak_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_peak_infections_7d_for_unvaccinated_students[3]) << "d";

                            }
                            if (tau_array_for_max_ratio_peak_infections_7d_for_unvaccinated_students[4] == 0) {
                                best_scenarios_peak_infections << "\t" << "N/A";
                            }
                            else
                            {
                                best_scenarios_peak_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_peak_infections_7d_for_unvaccinated_students[4]) << "d";

                            }
                            best_scenarios_peak_infections << "\t" << max_ratio_peak_infections_7d_for_unvaccinated_students << endl;

                            /////////////////////////////   Sreening every 3 days FOR UNVACCINATED STUDENTS
                            best_scenarios_peak_infections << OMEGA * 100 << "%" << "\t" << U_N_F_0 << "\t" << U_N_S_0 << "\t" << U_W_F_0 << "\t" << U_W_S_0 << "\t" << U_B_F_0 << "\t" << U_B_S_0 << "\t" << ETA << "\t" << GAMMA;
                            if (LAMBDA == 0)
                            {
                                best_scenarios_peak_infections << "\t" << 0;
                            }
                            else
                            {
                                best_scenarios_peak_infections << "\t" << 1.0 / (3 * LAMBDA * 7);
                            }

                            best_scenarios_peak_infections << "\t" << "3d";   //N_S 3d

                            if (tau_array_for_max_ratio_peak_infections_3d_for_unvaccinated_students[0] == 0)
                            {
                                best_scenarios_peak_infections << "\t" << "N/A";

                            }
                            else {
                                best_scenarios_peak_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_peak_infections_3d_for_unvaccinated_students[0]) << "d";

                            }

                            if (tau_array_for_max_ratio_peak_infections_3d_for_unvaccinated_students[1] == 0) {
                                best_scenarios_peak_infections << "\t" << "N/A";

                            }
                            else
                            {
                                best_scenarios_peak_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_peak_infections_3d_for_unvaccinated_students[1]) << "d";

                            }

                            if (tau_array_for_max_ratio_peak_infections_3d_for_unvaccinated_students[2] == 0) {
                                best_scenarios_peak_infections << "\t" << "N/A";

                            }
                            else {
                                best_scenarios_peak_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_peak_infections_3d_for_unvaccinated_students[2]) << "d";

                            }
                            if (tau_array_for_max_ratio_peak_infections_3d_for_unvaccinated_students[3] == 0)
                            {
                                best_scenarios_peak_infections << "\t" << "N/A";

                            }
                            else
                            {
                                best_scenarios_peak_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_peak_infections_3d_for_unvaccinated_students[3]) << "d";

                            }
                            if (tau_array_for_max_ratio_peak_infections_3d_for_unvaccinated_students[4] == 0) {
                                best_scenarios_peak_infections << "\t" << "N/A";
                            }
                            else
                            {
                                best_scenarios_peak_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_peak_infections_3d_for_unvaccinated_students[4]) << "d";

                            }
                            best_scenarios_peak_infections << "\t" << max_ratio_peak_infections_3d_for_unvaccinated_students << endl;

                            /////////////////////////////   Sreening every 2 days FOR UNVACCINATED STUDENTS
                            best_scenarios_peak_infections << OMEGA * 100 << "%" << "\t" << U_N_F_0 << "\t" << U_N_S_0 << "\t" << U_W_F_0 << "\t" << U_W_S_0 << "\t" << U_B_F_0 << "\t" << U_B_S_0 << "\t" << ETA << "\t" << GAMMA;
                            if (LAMBDA == 0)
                            {
                                best_scenarios_peak_infections << "\t" << 0;
                            }
                            else
                            {
                                best_scenarios_peak_infections << "\t" << 1.0 / (3 * LAMBDA * 7);
                            }

                            best_scenarios_peak_infections << "\t" << "2d";   //N_S 2d

                            if (tau_array_for_max_ratio_peak_infections_2d_for_unvaccinated_students[0] == 0)
                            {
                                best_scenarios_peak_infections << "\t" << "N/A";

                            }
                            else {
                                best_scenarios_peak_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_peak_infections_2d_for_unvaccinated_students[0]) << "d";

                            }

                            if (tau_array_for_max_ratio_peak_infections_2d_for_unvaccinated_students[1] == 0) {
                                best_scenarios_peak_infections << "\t" << "N/A";

                            }
                            else
                            {
                                best_scenarios_peak_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_peak_infections_2d_for_unvaccinated_students[1]) << "d";

                            }

                            if (tau_array_for_max_ratio_peak_infections_2d_for_unvaccinated_students[2] == 0) {
                                best_scenarios_peak_infections << "\t" << "N/A";

                            }
                            else {
                                best_scenarios_peak_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_peak_infections_2d_for_unvaccinated_students[2]) << "d";

                            }
                            if (tau_array_for_max_ratio_peak_infections_2d_for_unvaccinated_students[3] == 0)
                            {
                                best_scenarios_peak_infections << "\t" << "N/A";

                            }
                            else
                            {
                                best_scenarios_peak_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_peak_infections_2d_for_unvaccinated_students[3]) << "d";

                            }
                            if (tau_array_for_max_ratio_peak_infections_2d_for_unvaccinated_students[4] == 0) {
                                best_scenarios_peak_infections << "\t" << "N/A";
                            }
                            else
                            {
                                best_scenarios_peak_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_peak_infections_2d_for_unvaccinated_students[4]) << "d";

                            }
                            best_scenarios_peak_infections << "\t" << max_ratio_peak_infections_2d_for_unvaccinated_students << endl;

                            /////////////////////////////   Sreening every 1 days FOR UNVACCINATED STUDENTS
                            best_scenarios_peak_infections << OMEGA * 100 << "%" << "\t" << U_N_F_0 << "\t" << U_N_S_0 << "\t" << U_W_F_0 << "\t" << U_W_S_0 << "\t" << U_B_F_0 << "\t" << U_B_S_0 << "\t" << ETA << "\t" << GAMMA;
                            if (LAMBDA == 0)
                            {
                                best_scenarios_peak_infections << "\t" << 0;
                            }
                            else
                            {
                                best_scenarios_peak_infections << "\t" << 1.0 / (3 * LAMBDA * 7);
                            }

                            best_scenarios_peak_infections << "\t" << "1d";   //N_S 1d

                            if (tau_array_for_max_ratio_peak_infections_1d_for_unvaccinated_students[0] == 0)
                            {
                                best_scenarios_peak_infections << "\t" << "N/A";

                            }
                            else {
                                best_scenarios_peak_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_peak_infections_1d_for_unvaccinated_students[0]) << "d";

                            }

                            if (tau_array_for_max_ratio_peak_infections_1d_for_unvaccinated_students[1] == 0) {
                                best_scenarios_peak_infections << "\t" << "N/A";

                            }
                            else
                            {
                                best_scenarios_peak_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_peak_infections_1d_for_unvaccinated_students[1]) << "d";

                            }

                            if (tau_array_for_max_ratio_peak_infections_1d_for_unvaccinated_students[2] == 0) {
                                best_scenarios_peak_infections << "\t" << "N/A";

                            }
                            else {
                                best_scenarios_peak_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_peak_infections_1d_for_unvaccinated_students[2]) << "d";

                            }
                            if (tau_array_for_max_ratio_peak_infections_1d_for_unvaccinated_students[3] == 0)
                            {
                                best_scenarios_peak_infections << "\t" << "N/A";

                            }
                            else
                            {
                                best_scenarios_peak_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_peak_infections_1d_for_unvaccinated_students[3]) << "d";

                            }
                            if (tau_array_for_max_ratio_peak_infections_1d_for_unvaccinated_students[4] == 0) {
                                best_scenarios_peak_infections << "\t" << "N/A";
                            }
                            else
                            {
                                best_scenarios_peak_infections << "\t" << 1.0 / (3 * tau_array_for_max_ratio_peak_infections_1d_for_unvaccinated_students[4]) << "d";

                            }


                            best_scenarios_peak_infections << "\t" << max_ratio_peak_infections_1d_for_unvaccinated_students << endl;

                            best_scenarios_peak_infections << "Please check the customized results as well (they're in txt separate files)" << endl << endl;


                       // }

                   // }
              //  }

            } myfile_infections_table << endl;
        }myfile_infections_table << endl;
    }myfile_infections_table << endl;





    myfile_infections_table.close();
    myfile_screening_table.close();
    customized_scenarios_filtered.close();
    best_scenarios_total_infections.close();
    best_scenarios_peak_infections.close();


    return 0;
}
