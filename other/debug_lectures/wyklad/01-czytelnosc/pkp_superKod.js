/*
 * @returns {ObslugaKlopotliwychZnizek.o_k_z_module}
 */


function ObslugaKlopotliwychZnizek() {

         var KATEGORIA_POCIAG = {                  
                  EIC: [60, 29], 
                  EIP: [81], 
                  TLK: [0, 3, 33], 
                  IC: [30]
         };

         var BEZ_ZNIZKI = 1;
         var KLOPOTLIWE_ZNIZKI = {KOMBATANCI:67, WETERANI:85, WETERANI_74: 74 , CYWILNA_OFIARA: 87, KOMBATANT_INWALIDA: 83, INWALIDZI_WOJENNI_WOJSKOWI:82};     
         var ZNIZKI_PRACOWNIK_KOLEI = {PRACOWNIK_KOLEI:40, EMERYT_RENCISTA_KOLEI:41};
         var KLASA = {PIERWSZA:1, DRUGA:2};
         
         function validate(inputRef) {
             
            var isError = false;
            
            if(isZaznaczonoWieleZnizek_WybranoKlopotliwaZnizke()) {                 
                pokazKomunikatDlaWieluZnizek(inputRef);
                isError = true; 
                
            }else if(isZaznaczonoWieleZnizekKombatantInwalida()) {                            
                showOkienkoModalne(inputRef, "dalej_modal_klopotliwa_znizka_kombatant_przesiadka");
                isError = true; 
                  
            }else if(isPracownikEmerytKoleiDla2OdcinkowWieleZnizek()) {                                         
                showOkienkoModalne(inputRef, "dalej_modal_kolejarz_przesiadka");
                isError = true; 
            }
              
            return isError;
             
         }


          function run() {                    

              var poc_kategoria_odc_1 = parseInt($("#train_category_1").val());
              var poc_kategoria_odc_2 = parseInt($("#train_category_2").val());
              var klasa_wagonu = parseInt($("#klasa_wagonu").val());

              
               if(isPociagKat_TLK_IC(poc_kategoria_odc_1) && isPociagKat_EIP_EIC(poc_kategoria_odc_2) && isZaznaczonoKlopotliwaZnizke()) {                            
              
                    if((klasa_wagonu == KLASA.PIERWSZA && isZaznaczonoZnizke([KLOPOTLIWE_ZNIZKI.KOMBATANCI, KLOPOTLIWE_ZNIZKI.WETERANI])) 
                               || klasa_wagonu == KLASA.DRUGA && isZaznaczonoZnizke([KLOPOTLIWE_ZNIZKI.CYWILNA_OFIARA])) {                           
                          
                          pokazPola(false);    
                    } 
                    
                    aktywujPolaDlaDrugiegoOdcinkaDlaKatPoc_TLK_EIP();

               }else if(isPociagKat_EIP_EIC(poc_kategoria_odc_1) && isPociagKat_TLK_IC(poc_kategoria_odc_2)) {
                  
                  if(isZaznaczonoDowolnaZnizke()) {                      
                      pokazKomunikatZnizkiRozneKategorie();
                      ukryjKomunikatOBrakuZnizki();
                      pokazPola(true);                                              
                      
                  }else {
                      pokazLiczbeNOrazZnizke();                      
                  }                   
               }   

              return;
          } 

          function pokazPola(ustawicZnizke) {

              $("#tr_liczba_osob_n_2").show();
              
              if(!$("#wymiana_container").is(":visible")) {
                  $("#liczba_n_2").val(0);                    
              }             
              
              $("#kod_znizki_opis").addClass("przesiadka_hide_elem");      

              $("#kod_znizki_2_1, #kod_znizki_2_2, #kod_znizki_2_3").find("option").each(function(idx, elem) {                        
                  $(elem).removeAttr('disabled');                        
              });

              var ustawWartosci = function(znizki_odcinek_1_arr, znizki_odcinek_2_arr) {                      

                  var znizki_container = ["tr_kod_znizki", "tr_kod_znizki_2", "tr_kod_znizki_3"];
                  $.each(znizki_odcinek_1_arr, function(idx, elem) {

                      $("#" + znizki_odcinek_2_arr[idx]).val($("#" + elem).val());

                      if(parseInt($("#" + elem).val()) > 0) {                                

                          $("#" + znizki_odcinek_2_arr[idx]).show();                                
                          $("#" + znizki_container[idx]).removeClass("przesiadka_hide_elem");
                          $("#" + elem).closest(".znizki_wrapper_ulga_ilosc").removeClass("przesiadka_hide_elem");

                          var selector = "#kod_znizki_opis" + ((idx > 0) ? ("_" + (idx + 1)) : "");                                

                          $("#" + elem).closest(".form_wrapper").find(selector).removeClass("przesiadka_hide_elem");

                      }

                  });                        
              };
              
              

              if(ustawicZnizke) {

                  $("#liczba_n_2").val($("#liczba_n").val());
                  $("#kod_znizki_2_1").val($("#kod_znizki").val());     

                  var znizki_1_odcinek = ["liczba_u", "liczba_u_2", "liczba_u_3"];
                  var znizki_2_odcinek = ["liczba_u_2_1", "liczba_u_2_2", "liczba_u_2_3"];

                  ustawWartosci(znizki_1_odcinek, znizki_2_odcinek);
              }

          }
          
          function pokazLiczbeNOrazZnizke() {
              $("#tr_liczba_osob_n_2").show();
              $("#liczba_n_2").val(0);                      
              $("#tr_kod_znizki").removeClass("przesiadka_hide_elem");
              $("#liczba_u").addClass("przesiadka_hide_elem");
              $("#liczba_u_2_1").show();
              $("#rodzaj_ulgi_wrap_1, #rodzaj_ulgi_wrap_2").addClass("przesiadka_hide_elem");              
              $(".znizki_przesiadki_wrapper").show();         
              //$(".przesiadka_info_znizka_rozne_kategorie").show();
              
          } 

          function pokazKomunikatZnizkiRozneKategorie() {              
              $(".przesiadka_info_znizka_rozne_kategorie").show();
          }
          
          function ukryjKomunikatOBrakuZnizki() {
              $(".przesiadka_info_brak_znizki").hide();
          }

          function isPociagKat_EIP_EIC(poc_kategoria_nr) {                    
              var poc_kat_EIP_EIC_arr = KATEGORIA_POCIAG.EIP.concat(KATEGORIA_POCIAG.EIC);
              return (poc_kat_EIP_EIC_arr.indexOf(poc_kategoria_nr) > -1 );
          }

          function isPociagKat_TLK_IC(poc_kategoria_nr) {                    
              var poc_kat_TLK_IC_arr = KATEGORIA_POCIAG.TLK.concat(KATEGORIA_POCIAG.IC);
              return (poc_kat_TLK_IC_arr.indexOf(poc_kategoria_nr) > -1 );
          }

          function isPociagKat_EIP_EIC_AND_TLK_IC(poc_kategoria_odcinek_1, poc_kategoria_odcinek_2) {

              if(isPociagKat_EIP_EIC(poc_kategoria_odcinek_1) &&  isPociagKat_TLK_IC(poc_kategoria_odcinek_2)) {
                  return true;
              }

              return false;                    
          }
          
          function isPociagKat_TLK_IC_AND_EIP_EIC(poc_kategoria_odcinek_1, poc_kategoria_odcinek_2) {

              if(isPociagKat_TLK_IC(poc_kategoria_odcinek_1) &&  isPociagKat_EIP_EIC(poc_kategoria_odcinek_2)) {
                  return true;
              }

              return false;                    
          }
          
          


          /**
           * Sprwadzamy czy wybrano wiele znizek i czy na liscie jest kloptliwa znizka
           */
          function isZaznaczonoWieleZnizek_WybranoKlopotliwaZnizke() {

              var znizka_arr = ["kod_znizki", "kod_znizki_2", "kod_znizki_3"];                    
              var liczba_n = parseInt($("#liczba_n").val());              

              var DOMYSLNA_WARTOSC_VAL = 1;
              var WIELE_ZNIZEK_VAL = 2;

              var klopotliwe_znizki_arr = [KLOPOTLIWE_ZNIZKI.KOMBATANCI, KLOPOTLIWE_ZNIZKI.WETERANI, KLOPOTLIWE_ZNIZKI.CYWILNA_OFIARA];

              var ilosc_wybranych_znizek = 0;
              var isWybranoKlopotliwaZnizka = false;

              $.each(znizka_arr, function(index, elem) {

                  var wybrana_znizka = parseInt($("#" + elem).find(":selected").val());                  
                  if(klopotliwe_znizki_arr.indexOf(wybrana_znizka) > -1 ) {
                      isWybranoKlopotliwaZnizka = true;
                  }                        

                  if(wybrana_znizka > DOMYSLNA_WARTOSC_VAL ) {                            
                      ilosc_wybranych_znizek++;
                  }

              });

              if(isWybranoKlopotliwaZnizka && (ilosc_wybranych_znizek >= WIELE_ZNIZEK_VAL || liczba_n > 0)) {                        

                  var poc_kategoria_odc_1 = parseInt($("#train_category_1").val());
                  var poc_kategoria_odc_2 = parseInt($("#train_category_2").val());
                  var klasa_wagonu = parseInt($("#klasa_wagonu").val());

                  if((isPociagKat_TLK_IC(poc_kategoria_odc_1) && isPociagKat_EIP_EIC(poc_kategoria_odc_2) && klasa_wagonu == KLASA.PIERWSZA) 
                          || (isPociagKat_EIP_EIC(poc_kategoria_odc_1) && isPociagKat_TLK_IC(poc_kategoria_odc_2) && klasa_wagonu == KLASA.DRUGA)) {                          
                      return true;
                  }                        
              }

              return false;

          }



          function isZaznaczonoKlopotliwaZnizke() {

              var znizka_arr = ["kod_znizki", "kod_znizki_2", "kod_znizki_3"];                    
              var klopotliwe_znizki_arr = [KLOPOTLIWE_ZNIZKI.KOMBATANCI, KLOPOTLIWE_ZNIZKI.WETERANI, KLOPOTLIWE_ZNIZKI.CYWILNA_OFIARA];
              var isKlopotliwaZnizka = false;

               $.each(znizka_arr, function(index, elem) {

                  var wybrana_znizka = parseInt($("#" + elem).find(":selected").val());                  
                  if(klopotliwe_znizki_arr.indexOf(wybrana_znizka) > -1 ) {
                      isKlopotliwaZnizka = true;
                  }
              });

              return isKlopotliwaZnizka;
          }

          function isZaznaczonoDowolnaZnizke() {

              var znizka_arr = ["kod_znizki", "kod_znizki_2", "kod_znizki_3"];                      
              var zaznaczonoZnizke = false;

              $.each(znizka_arr, function(index, elem) {

                  var wybrana_znizka = parseInt($("#" + elem).find(":selected").val());        
                  if(wybrana_znizka > 1) {
                      zaznaczonoZnizke = true;
                  }
              });

               return zaznaczonoZnizke;
          }


          function isZaznaczonoZnizke(znizka_arr) {

              var znizka_arr_combo = ["kod_znizki", "kod_znizki_2", "kod_znizki_3"];                                        
              var isKlopotliwaZnizka = false;

               $.each(znizka_arr_combo, function(index, elem) {
                  var wybrana_znizka = parseInt($("#" + elem).find(":selected").val());                  
                  if(znizka_arr.indexOf(wybrana_znizka) > -1 ) {
                      isKlopotliwaZnizka = true;
                  }
              });

              return isKlopotliwaZnizka;
          }

          function pokazKomunikatDlaWieluZnizek(input_ref) {
              $("#dalej_modal_klopotliwa_znizka_przesiadka").show();
              $("#dalej_modal_ok").val("ok");
              $("#dalej_modal_footer").show();                        
              $("#dalej_modal_inform").hide();
              $("#dalej_modal_false").hide();                        
              $("#dalej_modal_ok").attr("type","button");                        
              $("#dalej_modal_ok").addClass("js-modal-close").click(function(event) {                        
                  $(input_ref).okienkoModalne().close(function() {
                      $(".dalej_modal").hide();
                  });                 
              });
              
              $(".js-modal-close").click(function(event) {                                                                              
                  $(input_ref).okienkoModalne().close(function() {
                      $(".dalej_modal").hide();                      
                  });                 
              });

              $(input_ref).okienkoModalne().open();     
          }

          function isPracownikEmerytKoleiDla2OdcinkowWieleZnizek() {

              var sprawdzZnizki = function(znizki) {
                
                var liczba_n = $("#liczba_n");
                
                var znizki_prac_kolei_arr = [ZNIZKI_PRACOWNIK_KOLEI.PRACOWNIK_KOLEI, ZNIZKI_PRACOWNIK_KOLEI.EMERYT_RENCISTA_KOLEI];
                
                var isKlopotliwaZnizka = false;
                var isNieKlopotliwaZnizka = false;

                $.each(znizki, function(idx, elem) {

                  var wybrana_znizka = parseInt($("#" + elem).find(":selected").val());                  
                  if(znizki_prac_kolei_arr.indexOf(wybrana_znizka) > -1 ) {
                      isKlopotliwaZnizka = true;
                  } else if (wybrana_znizka > 1) {
                      isNieKlopotliwaZnizka = true;
                  }

                });     
                

                return isKlopotliwaZnizka && (isNieKlopotliwaZnizka || liczba_n.val() > 0);

              }; // end functon

              var znizki_pierwszy_odcinek_arr = ["kod_znizki", "kod_znizki_2", "kod_znizki_3"];
              var znizki_drugi_odcinek_arr = ["kod_znizki_2_1", "kod_znizki_2_2", "kod_znizki_2_3"];

              var kategoriaPocOdcinek1 =  $("#train_category_1");
              var kategoriaPocOdcinek2 =  $("#train_category_2");                    

              if(kategoriaPocOdcinek1.val() != kategoriaPocOdcinek2.val()) {                        
                  if(sprawdzZnizki(znizki_pierwszy_odcinek_arr) 
                          || sprawdzZnizki(znizki_drugi_odcinek_arr)) {                        
                      return true;
                  }
              }
              
              return false;
          }
          
          function isZaznaczonoWieleZnizekKombatantInwalida() {
              
              var katPocOdcinek1 = parseInt($("#train_category_1").val());
              var katPocOdcinek2 =  parseInt($("#train_category_2").val());                    
              
              if(isPociagKat_TLK_IC_AND_EIP_EIC(katPocOdcinek1, katPocOdcinek2)) {
              
                var znizki_odcinek_arr = ["kod_znizki", "kod_znizki_2", "kod_znizki_3"];              
                var iloscZaznaczonychZnizek = 0;
                var isZaznaczonoKombatantInwalida = false;
                var liczba_n_val = parseInt($("#liczba_n").val());              

                $.each(znizki_odcinek_arr, function(idx, elem) {
                    var znizka = parseInt($("#" + elem).val());

                    if(znizka > BEZ_ZNIZKI) {
                        iloscZaznaczonychZnizek++;
                    }

                    if(znizka == KLOPOTLIWE_ZNIZKI.KOMBATANT_INWALIDA 
                            || znizka == KLOPOTLIWE_ZNIZKI.INWALIDZI_WOJENNI_WOJSKOWI) {

                        isZaznaczonoKombatantInwalida = true;
                    }
                });

                if((liczba_n_val > 0 && isZaznaczonoKombatantInwalida) || (iloscZaznaczonychZnizek > 1 && isZaznaczonoKombatantInwalida)) {
                    return true;
                }
            }
              
              return false;
              
          }

          function showOkienkoModalne(input_ref, modal_id) {
              
              $("#"+modal_id).show();
              $("#dalej_modal_ok").val("ok");
              $("#dalej_modal_footer").show();                        
              $("#dalej_modal_inform").hide();
              $("#dalej_modal_false").hide();                        
              $("#dalej_modal_ok").attr("type","button");                        
              $("#dalej_modal_ok").addClass("js-modal-close").click(function(event) {                        
                  $(input_ref).okienkoModalne().close();                                 
              });

              $(input_ref).okienkoModalne().open();                               

          }
          
          
          function pokazKomunikatRozneKatPoc_Eip_TLK() {              
             
              var kategoriaPocOdcinek1 =  $("#train_category_1").val();
              var kategoriaPocOdcinek2 =  $("#train_category_2").val();                    
              var przesiadka_info_znizka_rozne_kategorie = $(".przesiadka_info_znizka_rozne_kategorie");
             
              if(isPociagKat_EIP_EIC(parseInt(kategoriaPocOdcinek1)) && isPociagKat_TLK_IC(parseInt(kategoriaPocOdcinek2)) && isZaznaczonoDowolnaZnizke()) {                                   
                 przesiadka_info_znizka_rozne_kategorie.show();
              }else {                  
                 przesiadka_info_znizka_rozne_kategorie.hide();                  
              }     
              
          } 
          
          function aktywujPolaDlaDrugiegoOdcinkaDlaKatPoc_TLK_EIP() {
              
              var katPocOdcinek1 = parseInt( $("#train_category_1").val());
              var katPocOdcinek2 = parseInt($("#train_category_2").val());      
                            
              if(isPociagKat_TLK_IC_AND_EIP_EIC(katPocOdcinek1, katPocOdcinek2)) {
                  
                  var DEFAULT_VAL =0;
                  var BEZ_ZNIZKI = 1;
                  var MAX_ILOSC_ZNIZEK = 3;
                  var liczba_n = $("#liczba_n");                  
                  var liczba_u_odcinek_pierwszy_arr = ["liczba_u", "liczba_u_2", "liczba_u_3"];              
                  var znizki_odcinek_pierwszy_arr = ["kod_znizki", "kod_znizki_2", "kod_znizki_3"];
                  var znizkiDrugiOdcinek = {
                        combo : ["#kod_znizki_2_1", "#kod_znizki_2_2", "#kod_znizki_2_3"],
                        wrapper : ["#tr_kod_znizki", "#tr_kod_znizki_2", "#tr_kod_znizki_3"]                  
                  };
                  var znizki_wyjatki= [KLOPOTLIWE_ZNIZKI.KOMBATANCI, KLOPOTLIWE_ZNIZKI.WETERANI, KLOPOTLIWE_ZNIZKI.WETERANI_74];
                  
                  var iloscOsobPierwszyOdc = 0;
                  iloscOsobPierwszyOdc +=  parseInt(liczba_n.val());
                  
                  // zliczamy ilosc osob dla pierwszego odcinka
                  $.each(liczba_u_odcinek_pierwszy_arr, function(idx, elem){
                      
                      var liczba_u_val = parseInt($("#" + elem).val()); 
                      var znizka_val = parseInt($("#" + znizki_odcinek_pierwszy_arr[idx]).val());
                      
                      if(liczba_u_val > DEFAULT_VAL && znizka_val > BEZ_ZNIZKI) {
                          iloscOsobPierwszyOdc += liczba_u_val;
                      }
                      
                  });
                  
                  
                  // pokazujemy pola dla drugiego odcinka
                  if(iloscOsobPierwszyOdc > DEFAULT_VAL) {                      
                      
                      $("#tr_liczba_osob_n_2").show();
                      
                      for(var i=0; i<iloscOsobPierwszyOdc; i++) {
                          
                          if(i < MAX_ILOSC_ZNIZEK) {
                              
                            var znizka_wrapper = $(znizkiDrugiOdcinek.wrapper[i]);
                            var wybrana_znizka_odcinek_2 = parseInt($(znizkiDrugiOdcinek.combo[i]).find("option:selected").val());
                            
                            if(!(znizki_wyjatki.indexOf(wybrana_znizka_odcinek_2) > -1 )) {                                
                                 znizka_wrapper.removeClass("przesiadka_hide_elem");                              
                                 znizka_wrapper.find(".znizki_wrapper_ulga_ilosc").removeClass("przesiadka_hide_elem");                                                            
                            }
                            
                            znizka_wrapper.find("#liczba_u" + (i > 0 ? "_" + (i + 1) : "")).addClass("przesiadka_hide_elem");
                            znizka_wrapper.find("#liczba_u_2_" + (i+1)).show();
                            
                          }
                      }
                  }
              }
              
          }
          


         return {
             run : run,
             isZaznaczonoWieleZnizek_WybranoKlopotliwaZnizke : isZaznaczonoWieleZnizek_WybranoKlopotliwaZnizke,
             pokazKomunikatDlaWieluZnizek:pokazKomunikatDlaWieluZnizek,
             isPracownikEmerytKoleiDla2OdcinkowWieleZnizek : isPracownikEmerytKoleiDla2OdcinkowWieleZnizek,
             showOkienkoModalne:showOkienkoModalne,
             isPociagKat_EIP_EIC_AND_TLK_IC:isPociagKat_EIP_EIC_AND_TLK_IC,
             isPociagKat_TLK_IC_AND_EIP_EIC:isPociagKat_TLK_IC_AND_EIP_EIC,
             pokazKomunikatRozneKatPoc_Eip_TLK : pokazKomunikatRozneKatPoc_Eip_TLK,
             isZaznaczonoWieleZnizekKombatantInwalida:isZaznaczonoWieleZnizekKombatantInwalida,
             aktywujPolaDlaDrugiegoOdcinkaDlaKatPoc_TLK_EIP:aktywujPolaDlaDrugiegoOdcinkaDlaKatPoc_TLK_EIP,
             validate:validate

         };

     }


