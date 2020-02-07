
$.fn.zakupBiletu = function (options) {
    var zakup_biletu_form = $("#zakup_biletu_form");
    var nr_biletu_osoby_towarzyszacej = $("#nr_biletu_osoby_towarzyszacej");
    var rodzaj_wagonu = $("#rodzaj_wagonu");
    var dalej_button = $(".dalej_button");
    var klasa_wagonu = $("#klasa_wagonu");
    var tryb_posel = $("#tryb_posel");
    var przesiadkaPrev = $(".przesiadka_prev");
    var przesiadkaNext = $(".przesiadka_next");
    var arrow_box_ext_info = $(".arrow_box_ext_info");

    var nextStepPrzesiadka = 0;
    var ODCINEK = {
        PIERWSZY: 1,
        DRUGI: 2
    };

    // events 
    dalej_button.unbind('click').click(function (e) {

        var self = $(this);

        var strefaCiszyArr = [52, 11];
        var dlaPodrzDzieckiDoLat6Arr = [3,50];
        var rowerOferta = 15;
        var SIEDZACE = 1;

        var rodzajWagonu = parseInt($("#rodzaj_wagonu").find("option:selected").val());
        var rodzajWagonuOdcinek_1 = parseInt($("#rodzaj_wagonu_odcinek_2").val());
        var rower = $("#rodzaj_wagonu").find("option:selected").val();
        var krajowy = self.attr("krajowy");
        var kat_poc = self.attr("kat_poc");
        var is_bilet_rodzinny = $("#bilet_rodzinny").is(":checked");
        var is_przesiadka_zakupowa = ParamUtil.parseBoolean(self.attr("przesiadka"));
        var ignoruj_odc = false;
        if (self.attr("ignoruj_odc") !== null && self.attr("ignoruj_odc") !== undefined) {
            ignoruj_odc = ParamUtil.parseBoolean(self.attr("ignoruj_odc"));
        }
        if (ignoruj_odc) {
            is_przesiadka_zakupowa = false;
        }

        if (!validMiejsceSasiadujaceWskazane(ODCINEK.PIERWSZY)) {
            return; // blokujemy przycisk Dalej
        }

        if (!validNrBiletuOsobyTowarzyszacej()) {
            return;
        }

        var v1 = $("#dalej_modal_ok").attr("v1");
        var v2 = $("#dalej_modal_ok").attr("v2");
        var v3 = $("#dalej_modal_ok").attr("v3");
        var v4 = $("#dalej_modal_ok").attr("v4");

        var dalej_modal_false = true;
        var dalej_modal_atention = false;
        var dalej_modal_bilet_pies_caly_przedzial = false;
        var dalej_modal_jedno_lozko_dziecko_opiekun = false;


        $('.dalej_modal').each(function (index) {
            $(this).hide();
        });

        var openModal = false;

        if (krajowy) {

            // strefa ciszy
            if ((strefaCiszyArr.indexOf(rodzajWagonu) > -1 || strefaCiszyArr.indexOf(rodzajWagonuOdcinek_1) > -1) && !is_przesiadka_zakupowa) {
                openModal = true;
                $("#dalej_modal_strefa_ciszy").show();
                $("#dalej_modal_ok").val(v1);
            }

            // dla dziecka do lat 6
            if (nextStepPrzesiadka == 0) {
                if (dlaPodrzDzieckiDoLat6Arr.indexOf(rodzajWagonu) > -1 && !BilDodatkoweService().czyNieWybranoCalegoPrzedzialuDlaPsa()) {

                    var ile_osob = Number($("#liczba_n").find("option:selected").val()) + Number($("#liczba_u").find("option:selected").val()) + Number($("#liczba_u_2").find("option:selected").val());
                    if (ile_osob >= 2) {
                        if (kat_poc != 81 || ile_osob <= 4) {
                            openModal = true;
                            $("#dalej_modal_dla_podr_z_dzieckiem_do_lat_6").show();
                            $("#dalej_modal_ok").val(v1);
                        }
                    }
                }
            }

            // bilet rodzinny
            if (is_bilet_rodzinny) {

                var usluga_id = parseInt($(".rodzaj_miejsca:checked").val());
                var container_id = (usluga_id == SIEDZACE) ? 1 : 2;
                var usluga_wrapper = $("#rodzaj_ulgi_wrap_" + container_id);

                var liczba_n = $("#liczba_n").val();
                var kod_znizki = usluga_wrapper.find("#kod_znizki").val();
                var liczba_u = $("#liczba_u").val();

                var kod_znizki_2 = usluga_wrapper.find("#kod_znizki_2").val();
                var liczba_u_2 = $("#liczba_u_2").val();

                var ile_osob = Number(liczba_n) + Number(liczba_u) + Number(liczba_u_2);

                if (liczba_n == 0 && (Number(liczba_u) + Number(liczba_u_2)) > 0)
                {
                    openModal = true;
                    dalej_modal_false = false;
                    $("#dalej_modal_bilet_rodzinny_bledna_liczba_osob").show();
                    $("#dalej_modal_ok").val(v3);

                } else
                {
                    if ((liczba_u > 0 && kod_znizki == 77) || (liczba_u_2 > 0 && kod_znizki_2 == 77) || ile_osob < 2 || ile_osob > 5)
                    {

                    } else if (liczba_n >= 2 || (liczba_u > 0 && kod_znizki > 1) || (liczba_u_2 > 0 && kod_znizki_2 > 1))
                    {
                        openModal = true;
                        $("#dalej_modal_bilet_rodzinny").show();
                        $("#dalej_modal_ok").val(v2);
                    }


                    if (strefaCiszyArr && $("#dalej_modal_strefa_ciszy").is(":visible") && $("#dalej_modal_bilet_rodzinny").is(":visible"))
                    {
                        $("#dalej_modal_strefa_ciszy").hide();
                        $("#dalej_modal_bilet_rodzinny").hide();
                        $("#dalej_modal_bilet_rodzinny_strefa_ciszy").show();
                        $("#dalej_modal_ok").val(v2);
                    }
                }
            }

            /*** oblsuga modala dla pracownikow kolei ***/
            var ILOSC_OSOB_PRACOWNIK_KOLEI = 1; // dla 1 normalny submit, powy¿ej 1 pokazujemy modala
            if (iloscZaznaczonychZnizekPracownikKolei() > ILOSC_OSOB_PRACOWNIK_KOLEI) {
                openModal = true;
                $("#dalej_modal_pracownik_kolei").show();
            }


            if (BilDodatkoweService().czyNieWybranoCalegoPrzedzialuDlaPsa()) {
                openModal = true;
                dalej_modal_bilet_pies_caly_przedzial = true;
            }

            if (czyWybranoWspolneUsytuowanieNaJednymLozkuDzieckoOpiekun()) {
                openModal = true;
                dalej_modal_jedno_lozko_dziecko_opiekun = true;
            }



        } // end krajowy

        if ($(".bilet_dodatkowy").length > 0) {
            $(".bilet_dodatkowy").each(function (idx, obj) {

                var activeOption = $(obj).find("option:selected").val();
                if (parseInt(activeOption) == rowerOferta && !is_bilet_rodzinny) {
                    openModal = false;
                }

            });
        }

        if ($(this).attr("przesiadka") == "true")
        {
            var kat_1 = $(this).attr("kat_1");
            var kat_2 = $(this).attr("kat_2");

            if (kat_1 != kat_2)
            {
                if (czyZnalezionoZnizkiKolejarza()) {
                    openModal = true;
                    dalej_modal_atention = true;
                }
            }
        }

        if (openModal && (nextStepPrzesiadka == 0))
        {
            var modalService = new OknoModalneService();

            if (dalej_modal_atention) {
                modalService.dalejModalAtention();

            } else if (dalej_modal_bilet_pies_caly_przedzial) {
                modalService.dalejModalBiletPiesCalyPrzedzial();

            } else if (dalej_modal_jedno_lozko_dziecko_opiekun) {
                modalService.dalejModalJednoLozkoDzieckoOpiekun();

            } else if (dalej_modal_false) {
                modalService.dalejModalFalse();

            } else {
                modalService.dalejModalDefault();
            }

            // w przypadku przesiadki podmieniamy dla modala submita na button
            if (is_przesiadka_zakupowa) {

                $("#dalej_modal_ok").attr("type", "button").unbind('click').click(function (event) {

                    nextStepPrzesiadka++;
                    przesiadkiService(nextStepPrzesiadka);
                    $(this).okienkoModalne().close();
                });

            }

            $(this).okienkoModalne().open();

        } else if (is_przesiadka_zakupowa) {

            if (nextStepPrzesiadka == 0) { // odcinek 1

                if (ObslugaKlopotliwychZnizek().validate(this)) {
                    return;
                }
                informacja_pasazerska($(this).attr("nr_poc_2"), $(this).attr("data_odj_2"), $(this).attr("lang"));

                nextStepPrzesiadka++;
                przesiadkiService(nextStepPrzesiadka);
                return;


            } else if (nextStepPrzesiadka == 1) { // odcinek 2

                if (ObslugaKlopotliwychZnizek().validate(this)) {
                    return;
                }
                if (strefaCiszyArr.indexOf(rodzajWagonuOdcinek_1) > -1) {

                    prepareStrefaCiszyPrzesiadkiModal().unbind('click').click(function (event) {

                        nextStepPrzesiadka++;
                        przesiadkiService(nextStepPrzesiadka);

                        if (nextStepPrzesiadka > 1) {
                            document.forms['zakup_biletu_form'].submit();
                        }

                    });

                    $(this).okienkoModalne().open();
                    return;
                }

                if (czyWybranoDlaPodroznychZDziecmiDoLat6(this, dlaPodrzDzieckiDoLat6Arr, kat_poc)) {
                    return;
                }

                if (!validMiejsceSasiadujaceWskazane(ODCINEK.DRUGI)) {
                    return; // blokujemy przycisk Dalej
                }

                document.forms['zakup_biletu_form'].submit();

            }

        } else {

            document.forms['zakup_biletu_form'].submit();
        }



    });

    // przesiadki events
    przesiadkaPrev.click(function (event) {
        informacja_pasazerska($(this).attr("nr_poc_1"), $(this).attr("data_odj_1"), $(this).attr("lang"));
        nextStepPrzesiadka = 0;

        var przesiadka = new PrzesiadkiZakupowe();
        przesiadka.setIndexPrzesiadki(nextStepPrzesiadka);
        przesiadka.odblokujPolaDlaPrzesiadkiZakupowej();
        przesiadka.aktywujDeaktywujElementy();

        $().obslugaUlgi().obslugaWieluZnizek();

    });


    przesiadkaNext.click(function (event) {

        var przesiadka = new PrzesiadkiZakupowe();

        if (nextStepPrzesiadka == 0) {
            nextStepPrzesiadka++;
            przesiadka.setIndexPrzesiadki(nextStepPrzesiadka);
            przesiadka.aktywujDeaktywujElementy();

        }
        przesiadka.zablokujPolaDlaPrzesiadkiZakupowej();

    });

    arrow_box_ext_info.toggleClick(function () {

        $(this).closest(".data_box_section").find(".data_box_rwd").removeClass("data_box_hide").addClass("data_box_show");
        $(this).removeClass('arrow_box_down').addClass('arrow_box_up');

    }, function () {
        $(this).closest(".data_box_section").find(".data_box_rwd").removeClass("data_box_show").addClass("data_box_hide");
        $(this).removeClass('arrow_box_up').addClass('arrow_box_down');

    });

    zakup_biletu_form.submit(function () {

        // obsluga ulgi 100% Dla dziecka do lat 4              
        if (nr_biletu_osoby_towarzyszacej.is(':visible')) {
            if (nr_biletu_osoby_towarzyszacej.val().trim().length == 0) {
                nr_biletu_osoby_towarzyszacej.next().show();
                return false;
            }
        }

        /*********************/


        return true;

    });

    rodzaj_wagonu.change(function () {
        var kod_wagonu = $(this).find("option:selected").attr("value");
        rodzajWagonuOpis(kod_wagonu);
        sprawdzRowerRodzajWagonu();
        usunInformacjeWstepnaDlaPrzedzialDzieckoDo6Lat();

    });

    klasa_wagonu.change(function () {
        if (tryb_posel.length == 0) {
            ustawKlasaWagonu();
        }
        //    dzieckoDoLat6();

    });

    function iloscZaznaczonychZnizekPracownikKolei() {

        //PRACOWNIK_KOLEI : 40, EMERYT_RENCISTA_KOLEI : 41, PRACOWNIK_KOLEI_RODZINA : 42, PRACOWNIK_KOLEI_ZAPLECZE_TECHNICZNE : 44
        var pracownik_kolei_znizki = [40, 41, 42, 44];
        var kod_znizki_arr = ["kod_znizki", "kod_znizki_2", "kod_znizki_3"];
        var ilosc_arr = ["liczba_u", "liczba_u_2", "liczba_u_3"];

        var laczna_ilosc_osob_pracownik_kolei = 0;
        $.each(kod_znizki_arr, function (idx, elem) {

            var zaznaczona_znizka = parseInt($("#" + elem).find("option:selected").val());

            if (pracownik_kolei_znizki.indexOf(zaznaczona_znizka) > -1) {

                var liczba_u_elem = ilosc_arr[idx];
                var liczba_u_ilosc = parseInt($("#" + liczba_u_elem).find("option:selected").val());
                laczna_ilosc_osob_pracownik_kolei += liczba_u_ilosc;

            }
        });

        return laczna_ilosc_osob_pracownik_kolei;

    }


    function przesiadkiService(nextStepPrzesiadka) {

        var przesiadka = new PrzesiadkiZakupowe();
        przesiadka.setIndexPrzesiadki(nextStepPrzesiadka);
        przesiadka.zablokujPolaDlaPrzesiadkiZakupowej();
        przesiadka.aktywujDeaktywujElementy();

        ObslugaKlopotliwychZnizek().pokazKomunikatRozneKatPoc_Eip_TLK();

    }

    function prepareStrefaCiszyPrzesiadkiModal() {

        $("#dalej_modal_inform").hide();
        $("#dalej_modal_strefa_ciszy").show();
        $("#dalej_modal_footer").show();

        var modal = $("#dalej_modal_ok");

        var v1 = modal.attr("v1");
        modal.val(v1);
        modal.attr("type", "button");
        modal.addClass("js-modal-close");

        return modal;

    }

    function validMiejsceSasiadujaceWskazane(odcinek) {

        var MIEJSCE = {
            ZAJETE: "rezerwacja_obok_miejsca_juz_zajetego",
            WSKAZANE: "rezerwacja_miejsca_wskazanego"
        };

        var isWrongFormat = function (odcinek) {

            var elementy_nr = ["numer_wagonu", "numer_miejsca"];
            var flag = false;

            $.each(elementy_nr, function (idx, elem) {
                var idx = (odcinek > 1) ? "_" + odcinek : "";
                var input = $("#" + elem + idx);
                if (input.val().length > 0) {
                    if (!input.val().match(/^\d+$/)) {
                        input.addClass("error_input").closest(".form_wrapper_input").find(".error_info_wskazane_zajete").removeClass("display-hide");
                        flag = true;
                    } else {
                        input.removeClass("error_input").closest(".form_wrapper_input").find(".error_info_wskazane_zajete").addClass("display-hide");
                    }
                }
            });


            return flag;

        };

        var idx = (odcinek > 1) ? "_" + odcinek : "";

        if ($("#" + MIEJSCE.ZAJETE).is(":checked") || $("#" + MIEJSCE.WSKAZANE + idx).is(":checked")) {
            return !isWrongFormat(odcinek);
        }

        return true;

    }
    ;


        function czyWybranoWspolneUsytuowanieNaJednymLozkuDzieckoOpiekun() {
            
            var BEZ_ZNIZKI = 1;
            var znizkiDzieciMlodziez = [71, 77, 78];
            
            var liczba_lozek = $("#llozek");
            var liczba_n = $("#liczba_n");
            
            var kod_znizki_arr = ["kod_znizki", "kod_znizki_2", "kod_znizki_3"];
            var liczba_u_arr = ["liczba_u", "liczba_u_2", "liczba_u_3"];
            var liczba_doroslych = 0; 
            var liczba_dzieci = 0;
            var osobne_lozko_dla_dziecka_wrapper = $("#osobne_lozko_dla_dziecka_wrapper");
            if(liczba_lozek.is(":visible")) {
                
                liczba_doroslych += parseInt(liczba_n.val());
                
                $.each(kod_znizki_arr, function(idx, elem) {
                    
                    var kod_znizka = parseInt($("#" + elem).val());
                    var liczba_u = parseInt($("#" + liczba_u_arr[idx]).val());
                    
                    if (znizkiDzieciMlodziez.indexOf(kod_znizka) > -1) {                                              
                        liczba_dzieci += liczba_u;
                    }else if(kod_znizka != BEZ_ZNIZKI) {
                        liczba_doroslych += liczba_u;
                    }
                    
                    
                });
                osobne_lozko_dla_dziecka_wrapper.hide(); 
               $("#osobne_lozko_dla_dziecka").attr('checked', false);
                var liczba_osob_ogolem = liczba_dzieci + liczba_doroslych;

                 if(parseInt(liczba_lozek.val()) == 0) {
                     return false;
                     
                 }else if(liczba_osob_ogolem > parseInt(liczba_lozek.val())) {                    
                    return true;
                }
                
            }
            
            return false;
        }
        

    function czyWybranoDlaPodroznychZDziecmiDoLat6(inputref, dlaPodrzDzieckiDoLat6Arr, katPoc) {

        var flag = false;
        var rodzaj_wagonu_odcinek_2 = parseInt($("#rodzaj_wagonu_odcinek_2").find("option:selected").val());

        if (dlaPodrzDzieckiDoLat6Arr.indexOf(rodzaj_wagonu_odcinek_2) > -1) {

            var ile_osob = 0;
            var ids_liczba_osob_arr = ["liczba_n", "liczba_u_2_1", "liczba_u_2_2"];

            $(ids_liczba_osob_arr).each(function (idx, elem) {
                ile_osob += parseInt($("#" + elem).find("option:selected").val());
            });

            if (ile_osob >= 2) {
                if (katPoc != 81 || ile_osob <= 4) {

                    $(".dalej_modal").hide();
                    $("#dalej_modal_inform").hide();
                    $("#dalej_modal_dla_podr_z_dzieckiem_do_lat_6").show();
                    $("#dalej_modal_footer").show();

                    var modal = $("#dalej_modal_ok");
                    var v1 = modal.attr("v1");
                    modal.val(v1);
                    modal.attr("type", "button");
                    modal.addClass("js-modal-close").unbind('click').click(function (event) {
                        document.forms['zakup_biletu_form'].submit();
                    });

                    flag = true;

                    $(inputref).okienkoModalne().open();

                }
            }

        }

        return flag;

    }

    function validNrBiletuOsobyTowarzyszacej() {

        var nr_biletu_osoby_towarzyszacej = $("#nr_biletu_osoby_towarzyszacej");
        var nr_osoba_towarz_error = $(".nr_osoba_towarz_error");
        var regex = /^[0-9]+$/;
        var isPoprawny = true;

        if (nr_biletu_osoby_towarzyszacej.is(':visible')) {
            if (nr_biletu_osoby_towarzyszacej.val().trim().length == 0 || !regex.test(nr_biletu_osoby_towarzyszacej.val())) {
                nr_osoba_towarz_error.find("span").show();
                isPoprawny = false;
            } else {
                nr_osoba_towarz_error.find("span").hide();
                isPoprawny = true;
            }
        }

        return isPoprawny;
    }


    function czyZnalezionoZnizkiKolejarza() {

        var znizkaKolejarzPracownikIEmeryt = [40, 41];
        var znizkaKolejarzRodzina = [42, 44];

        //Badanie czy wybrano zni¿ki kolejarsie oraz inne
        var znizki_arr = ["kod_znizki", "kod_znizki_2", "kod_znizki_3", "kod_znizki_2_1", "kod_znizki_2_2", "kod_znizki_2_3"];
        var znalezionoZnizkaKolejarzRodzina = false;
        var znalezionoZnizkaKolejarzPracownikIEmeryt = false;

        $.each(znizki_arr, function (key, elem) {
            var zaznaczona_znizka = parseInt($("#" + elem).find(":selected").val());

            if (znizkaKolejarzRodzina.indexOf(zaznaczona_znizka) > -1) {
                znalezionoZnizkaKolejarzRodzina = true;
            }
            if (znizkaKolejarzPracownikIEmeryt.indexOf(zaznaczona_znizka) > -1) {
                znalezionoZnizkaKolejarzPracownikIEmeryt = true;
            }

        });

        return (znalezionoZnizkaKolejarzRodzina && znalezionoZnizkaKolejarzPracownikIEmeryt);

    }



    function PrzesiadkiZakupowe() {

        var elementyOnChange = "#zakup_biletu_form input[type='checkbox'], #zakup_biletu_form input[type='radio'], #zakup_biletu_form select";
        var elementy = {
            id: ["tr_rodzaj_miejsca", "tr_promocja", "tr_liczba_osob_n", "tr_kod_znizki", "tr_kod_znizki_2", "tr_kod_znizki_3",
                "tr_nr_taryfy_II", "tr_nr_taryfy_I", "tr_przedzial", "tr_plec", "tr_klasa",
                "tr_kolorowa_karta_ic", "tr_pokaz_kolorowa_karte", "tr_bilety_dodatkowe"],
            klasa: ["bilet_karta_rodziny_main_wrapper"]
        };


        this.indexPrzesiadki = 0;

        var odcinek = {PIERWSZY: 0, DRUGI: 1};

        this.zablokujPolaDlaPrzesiadkiZakupowej = function () {

            var elementsToShow = [
                ".submit_powrot_zakup_biletu",
                ".dalej_button",
                ".przesiadka_info_parametry",
                "#rodzaj_wagonu_odcinek_2",
                "#usytuowanie_przesiadka_1"

            ];

            // blokujemy KDR, BR
            $(".opcja_biletu_rodzinny").each(function () {

                var self = $(this);

                if (self.is(":checked")) {
                    _addInputKDFiBR(self, 1);
                } else {
                    _addInputKDFiBR(self, 0);
                }

            });

            $("#pokaz_kolorowa_karte").attr('disabled', true);

            // blokujemy us³ugi (siedzace, sypialne kuszetka)
            $(".rodzaj_miejsca").each(function (idx) {

                var self = $(this);
                if (!self.is(":checked")) {
                    self.attr('disabled', true);
                }
            });


            // usuwamy X z biletów dodatkowych
            $(".remove_additional_ticket").each(function (idx) {
                var self = $(this);
                self.hide();
            });

            _ustawMiejsceZajeteWskazaneMIejsce(false);
            _pokazUkryjElementyDlaPrzesiadek(elementy, false);

            $.each(elementsToShow, function (key, elem) {
                $(elem).show();
            });

            $("#rodzaj_wagonu, #usytuowanie").hide();

            this.obslugaZnizkeDlaPrzesiadki();
            $("#tr_pokaz_karte_duzej_rodziny").hide();
            $("#tr_pokaz_bilet_rodzinny").hide();



        };

        this.odblokujPolaDlaPrzesiadkiZakupowej = function () {

            var elementsToHide = [
                ".submit_powrot_zakup_biletu",
                ".przesiadka_info_parametry",
                "#rodzaj_wagonu_odcinek_2",
                "#usytuowanie_przesiadka_1",
                "#tr_liczba_osob_n_2",
                "#liczba_u_2_1",
                "#liczba_u_2_2",
                "#liczba_u_2_3"
            ];

            var elementsToShow = ["#liczba_u", "#liczba_u_2", "#liczba_u_3"];

            // usuwamy blokade  dla wszystkich elementow                   
            /*
             $(".opcja_biletu_rodzinny").each(function() {
             var self = $(this);                    
             
             });
             */
            // uswamy fake dla KDR i BR                    
            _removeInputKDRiBR();

            $("#pokaz_kolorowa_karte").attr('disabled', false);

            // odblokujemy us³ugi (siedzace, sypialne kuszetka)
            $(".rodzaj_miejsca").each(function (idx) {

                var self = $(this);
                self.attr('disabled', false);

            });

            // usuwamy X z biletów dodatkowych
            $(".remove_additional_ticket").each(function (idx) {
                var self = $(this);
                self.show();
            });


            _ustawMiejsceZajeteWskazaneMIejsce(true);
            _pokazUkryjElementyDlaPrzesiadek(elementy, true);


            $.each(elementsToHide, function (key, elem) {
                $(elem).hide();
            });

            $.each(elementsToShow, function (key, elem) {
                $(elem).removeClass("przesiadka_hide_elem");
            });

            $("#rodzaj_wagonu, #usytuowanie").show();

            this.obslugaZnizkeDlaPrzesiadki();

        };

        this.aktywujDeaktywujElementy = function () {

            var indexPrzesiadki = this.getindexPrzesiadki();

            $(".przesiadka_linia_wrapper").each(function (index) {

                var self = $(this);

                if (index == indexPrzesiadki) {
                    self.removeClass("przesiadka_linia_deactive").addClass("przesiadka_linia_active");
                } else {
                    self.removeClass("przesiadka_linia_active").addClass("przesiadka_linia_deactive");
                }
            });

            $(".przesiadka_konfiguracja_wypis").each(function (index) {

                var self = $(this);

                if (index == indexPrzesiadki) {
                    self.show();
                } else {
                    self.hide();
                }
            });

            if (indexPrzesiadki == 0) {
                $(".przesiadka_prev_bg").addClass("przesiadka_aktywny_odcinek");
                $(".przesiadka_next_bg").removeClass("przesiadka_aktywny_odcinek");

            } else {

                $("#rodzaj_wagonu_msg").hide();
                $(".przesiadka_prev_bg").removeClass("przesiadka_aktywny_odcinek");
                $(".przesiadka_next_bg").addClass("przesiadka_aktywny_odcinek");
            }

            // ustawiamy index odcinka w elemencie html na potrzeby innych modulow
            $("#indexPrzesiadki").val(indexPrzesiadki);

            var klasa_poc1 = $("#klasa_wagonu").find("option:selected").val();
            var klasa_poc2 = $("#klasa_wagonu").find("option:selected").val();

            if (klasa_poc1 !== klasa_poc2) {
                $("#klasa_wagonu").val(klasa_poc1);
            }

            $(".przesiadka_info_znizka_rozne_kategorie").hide();

            this.obslugaBiletRodzinny_DuzaRodzina();

        };

        this.obslugaZnizkeDlaPrzesiadki = function () {

            var indexOdcinek = this.getindexPrzesiadki();

            var znizkiPierwszyOdcinek = ["#kod_znizki", "#kod_znizki_2", "#kod_znizki_3"];
            var znizkiDrugiOdcinek = {
                combo: ["#kod_znizki_2_1", "#kod_znizki_2_2", "#kod_znizki_2_3"],
                wrapper: ["#tr_kod_znizki", "#tr_kod_znizki_2", "#tr_kod_znizki_3"]
            };



            if (indexOdcinek > 0) {
                this.pobierzZnizkiDlaPrzesiadki();

            } else { // obsluga pierwszego odcinka                      

                var liczba_n = $("#liczba_n");
                var liczba_u = $("#liczba_u");
                var kod_znizki = $("#kod_znizki");

                $(znizkiDrugiOdcinek.wrapper).each(function (key, elem) {

                    var znizka_wrapper = $(elem);
                    znizka_wrapper.removeClass("przesiadka_hide_elem");
                    znizka_wrapper.find(".znizki_wrapper_ulga_ilosc").removeClass("przesiadka_hide_elem");
                    znizka_wrapper.find("#liczba_u").removeClass("przesiadka_hide_elem");
                    znizka_wrapper.find(".znizki_wrapper_ulga_nazwa").find("div").each(function (key, elem) {

                        if ($(elem).attr("class") == "znizki_przesiadki_wrapper") {
                            $(elem).val(1);
                            $(elem).hide();
                        } else {
                            $(elem).removeClass("przesiadka_hide_elem");
                        }
                    });

                });

                var isWybranoZnizke = false;
                $.each(znizkiPierwszyOdcinek, function (key, elem) {
                    if (parseInt($(elem).val()) > 1) {
                        isWybranoZnizke = true;
                    }
                });

                if (isWybranoZnizke) {
                    $("#tr_miejsce_wskazane").hide();
                } else {
                    $("#tr_miejsce_wskazane").show();
                }

                $(".znizki_przesiadki_wrapper").hide();
                $("#kod_znizki_opis").removeClass("przesiadka_hide_elem");
                $(".przesiadka_info_brak_znizki").hide();
                //$(".przesiadka_info_znizka_rozne_kategorie").hide();

                var znizki_pracownika_kolei_arr = [77, 79, 84];

                var wybrana_znizka = parseInt(kod_znizki.val());
                if (liczba_n.val() == 0 && liczba_u.val() == 1 && znizki_pracownika_kolei_arr.indexOf(wybrana_znizka) < 0) {
                    $("#tr_miejsce_wskazane").show();
                }
            }


        };



        this.pobierzZnizkiDlaPrzesiadki = function () {


            $.ajax({
                method: "GET",
                url: "/zakup-biletu-utils",
                cache: false,
                data: {
                    action: "pobierzZnizkiPrzesiadki",
                    karta_duzej_rodziny: $("#karta_duzej_rodziny").is(":checked"),
                    bilet_rodzinny: $("#bilet_rodzinny").is(":checked"),
                    klasa_wagonu: $("#klasa_wagonu").val()

                },
                beforeSend: function (xhr) {
                    $(".zakup_biletu_form_main_wrapper").append(addMaskHtml());
                },
                success: function (data) {

                    var result = JSON.parse(data);
                    wype³nijCombaDlaPrzesiadki(result);
                    obslugaZnizekDlaOdcinkow();
                    ObslugaKlopotliwychZnizek().run();
                    obslugaElementowDlaPrzesiadki();
                    //        dzieckoDoLat6();

                },
                complete: function (r) {
                    removeMaskHtml();
                },
                error: function (xhr, status, thrownError) {
                }

            });




            function wype³nijCombaDlaPrzesiadki(options) {

                var comboZnizki = ["#kod_znizki", "#kod_znizki_2", "#kod_znizki_3"];
                var znizkiComboPrzesiadka = ["#kod_znizki_2_1", "#kod_znizki_2_2", "#kod_znizki_2_3"];


                $.each(comboZnizki, function (key, elem) {

                    var selectedOption = $(elem).find("option:selected");

                    if (selectedOption.val() > 0) {

                        var combo = $(znizkiComboPrzesiadka[key]);
                        combo.html('');
                        var znizkiCombos = options["znizki_" + key];

                        for (var i = 0; i < znizkiCombos.length; i++) {
                            combo.append(znizkiCombos[i].option);
                        }
                    }
                });
            }
            ;

            function obslugaElementowDlaPrzesiadki() {

                var PIERWSZY_ODCINEK = 1;
                var dalej_button = $(".dalej_button");

                //if(dalej_button.attr("przesiadka") == "true") { // sprawdzamy czy mamy doczynienia z przesiadka

                var indexOdcinek = parseInt($("#indexPrzesiadki").val());
                if (indexOdcinek == PIERWSZY_ODCINEK) {

                    var przesiadkiPola = ["kod_znizki_2_1", "kod_znizki_2_2", "kod_znizki_2_3"];
                    var isWybranoZnizke = false;
                    $.each(przesiadkiPola, function (key, elem) {
                        if (parseInt($("#" + elem).val()) > 1) {
                            isWybranoZnizke = true;
                        }
                    });

                    if (isWybranoZnizke) {
                        //$("#tr_miejsce_wskazane").hide();
                        $("#tr_rezerwacja_obok_miejsca_juz_zajetego_wagon_2").hide();
                        $("#tr_rezerwacja_obok_miejsca_juz_zajetego_miejsce_2").hide();
                        $("#rezerwacja_miejsca_wskazanego_2").prop("checked", false);
                        $("#numer_wagonu_2").val('');
                        $("#numer_miejsca_2").val('');
                    } else {
                        $("#tr_miejsce_wskazane").show();
                    }

                }
                //}

            }

            function obslugaZnizekDlaOdcinkow() {

                var znizkiPierwszyOdcinek = ["#kod_znizki", "#kod_znizki_2", "#kod_znizki_3"];
                var znizkiDrugiOdcinek = {
                    combo: ["#kod_znizki_2_1", "#kod_znizki_2_2", "#kod_znizki_2_3"],
                    wrapper: ["#tr_kod_znizki", "#tr_kod_znizki_2", "#tr_kod_znizki_3"]
                };

                var liczbaUlgArr = [
                    ["liczba_u", "liczba_u_2_1"],
                    ["liczba_u_2", "liczba_u_2_2"],
                    ["liczba_u_3", "liczba_u_2_3"]
                ];

                var iloscZaznaczonychZnizek = 0;
                var zaznaczoneZnizkiPierwszyOdcinek = [];
                var wybraneZnizkiDrugiOdcinek = [];
                var clearZnizkaDrugiOdcinek = [false, false, false];
                var brakujacaZnizkaDrugiOdcinek = {};

                $.each(znizkiPierwszyOdcinek, function (key, elem) {

                    // pobieramy zaznaczona znizke dla pierwszego odcinka                      
                    var zaznaczonaZnizkaOdcinekPierwszy = $(elem).find("option:selected");
                    var znizkaKodPierwszyOdcinek = zaznaczonaZnizkaOdcinekPierwszy.val();
                    var znizkaNazwaPierwszyOdcinek = zaznaczonaZnizkaOdcinekPierwszy.text();

                    zaznaczoneZnizkiPierwszyOdcinek.push({id: znizkaKodPierwszyOdcinek, nazwa: znizkaNazwaPierwszyOdcinek});

                    if (znizkaKodPierwszyOdcinek > 1) {
                        iloscZaznaczonychZnizek++;
                    }

                    var znizkiOpcjeDrugiOdcinek = znizkiDrugiOdcinek.combo[key];

                    $(znizkiOpcjeDrugiOdcinek).find("option").each(function (key1, elem1) {

                        var znizkaDrugiOdcinek = $(elem1);
                        if (znizkaKodPierwszyOdcinek > 1) {                            
                            
                            if (/*(znizkaKodPierwszyOdcinek == znizkaDrugiOdcinek.val()) && */ 
                                    (znizkaNazwaPierwszyOdcinek.trim() == znizkaDrugiOdcinek.text().trim())) {
                                
                                
                                clearZnizkaDrugiOdcinek[key] = true;
                                wybraneZnizkiDrugiOdcinek.push({id: znizkaDrugiOdcinek.val(), nazwa: znizkaDrugiOdcinek.text()});
                            }
                        }
                    }); // end each                          
                });   // end each    


                var i = 0;
                for (i; i < iloscZaznaczonychZnizek; i++) {

                    // sprawdzamy czy znizka nie wystepuje dla drugiego odcinka

                    if (clearZnizkaDrugiOdcinek[i] == false) {
                        brakujacaZnizkaDrugiOdcinek = zaznaczoneZnizkiPierwszyOdcinek[i];
                    }

                    // pokazujemy znizki dla drugiego odcinka 
                    var znizkaWrapper = $(znizkiDrugiOdcinek.wrapper[i]);
                    //znizkaWrapper.removeClass("przesiadka_hide_elem");
                    znizkaWrapper.find(".znizki_wrapper_ulga_ilosc").addClass("przesiadka_hide_elem");
                    znizkaWrapper.find("#liczba_u" + (i > 0 ? "_" + (i + 1) : "")).addClass("przesiadka_hide_elem");
                    znizkaWrapper.find(".znizki_wrapper_ulga_nazwa").find("div").each(function (key, elem) {

                        if ($(elem).attr("class") != "znizki_przesiadki_wrapper") {
                            $(elem).addClass("przesiadka_hide_elem");
                        } else {
                            $(elem).show();
                        }
                    });

                    if (wybraneZnizkiDrugiOdcinek[i] != undefined) {
                        $(znizkiDrugiOdcinek.combo[i]).val(wybraneZnizkiDrugiOdcinek[i].id);
                    }

                }

                if (brakujacaZnizkaDrugiOdcinek.id != undefined) {
                    
                   var poc_kategoria_odc_1 = parseInt($("#train_category_1").val());
                   var poc_kategoria_odc_2 = parseInt($("#train_category_2").val());
                   var okz = ObslugaKlopotliwychZnizek();                   
                   
                   
                   if(okz.isPociagKat_EIP_EIC_AND_TLK_IC(poc_kategoria_odc_1, poc_kategoria_odc_2) 
                           || okz.isPociagKat_TLK_IC_AND_EIP_EIC(poc_kategoria_odc_1, poc_kategoria_odc_2)) {
                     
                        var przesiadka_info_brak_znizki = $(".przesiadka_info_brak_znizki");
                        przesiadka_info_brak_znizki.show();
                        przesiadka_info_brak_znizki.find("span").empty().append("\"" + brakujacaZnizkaDrugiOdcinek.nazwa + "\"");
                   }   
                   
                    $("#kod_znizki_opis").addClass("przesiadka_hide_elem");
                    $("#tr_liczba_osob_n_2").show();

                    for (var i = 0; i < iloscZaznaczonychZnizek; i++) {

                        var znizkaWrapper = $(znizkiDrugiOdcinek.wrapper[i]);
                        znizkaWrapper.removeClass("przesiadka_hide_elem");
                        znizkaWrapper.find(".znizki_wrapper_ulga_ilosc").removeClass("przesiadka_hide_elem");
                        znizkaWrapper.find("#liczba_u_2_" + (i + 1)).show();
                    }                       
                   

                } else {
                    
                    $("#liczba_n_2").val($("#liczba_n").val());

                    // ustwiamy liczbe osob ulgowych dla drugiego odcinka
                    $(liczbaUlgArr).each(function (key, elem) {
                        $("#" + elem[1]).val($("#" + elem[0]).val());
                    });

                    $(wybraneZnizkiDrugiOdcinek).each(function (key, elem) {

                        var znizkaDrugiOdcinekElement = $(elem);
                        var znizkiDrugiOdcinekCombo = znizkiDrugiOdcinek.combo[key];

                        $(znizkiDrugiOdcinekCombo).find("option").each(function (key1, elem1) {                          
                          
                            if (znizkaDrugiOdcinekElement[0].nazwa.trim() != $(elem1).text().trim()) {
                                $(elem1).prop("disabled", "disabled");
                            } else {
                                $(elem1).prop("selected", "selected");
                            }
                        });                        

                    });

                }

            }
            ;

            function addMaskHtml() {
                var html = "<div class=\"loadmask\"></div>";
                return html;
            }
            ;
            function removeMaskHtml() {
                $(".loadmask").remove();
            }



        };

        this.obslugaBiletRodzinny_DuzaRodzina = function () {

            var indexOdcinek = parseInt(this.getindexPrzesiadki());

            var KDR_BR_elementy = [
                ["karta_duzej_rodziny", "tr_pokaz_karte_duzej_rodziny"],
                ["bilet_rodzinny", "tr_pokaz_bilet_rodzinny"]
            ];

            for (var i = 0; i < KDR_BR_elementy.length; i++) {

                if ($("#" + KDR_BR_elementy[i][0]).is(":checked")) {

                    var label_element = $("#" + KDR_BR_elementy[i][1]).find(".form_wrapper_input");

                    if (indexOdcinek == odcinek.PIERWSZY) {
                        label_element.removeClass("przesiadka_hide_elem");
                    } else if (indexOdcinek == odcinek.DRUGI) {
                        label_element.addClass("przesiadka_hide_elem");
                    }

                }

            }

        };


        this.setIndexPrzesiadki = function (currentIndex) {
            this.indexPrzesiadki = currentIndex;
        };

        this.getindexPrzesiadki = function () {
            return this.indexPrzesiadki;
        };

        // private methods
        function _addInputKDFiBR(elem, value) {
            $("#zakup_biletu_form").append("<input class=\"opcja_biletu_rodzinny_mock display-hide\" type=\"checkbox\" name=\"" + elem.attr("name") + "\" value=\"" + value + "\" />");
        }
        ;

        function _removeInputKDRiBR() {
            $("#zakup_biletu_form").find(".opcja_biletu_rodzinny_mock").remove();
        }
        ;

        function _ustawMiejsceZajeteWskazaneMIejsce(ustawicPierwszyOdcinek) {


            var elementyAktywneIds = [
                "rezerwacja_obok_miejsca_juz_zajetego",
                "rezerwacja_miejsca_wskazanego",
                "tr_rezerwacja_obok_miejsca_juz_zajetego_wagon",
                "tr_rezerwacja_obok_miejsca_juz_zajetego_miejsce"
            ];
            var suffix_2 = "_2";

            var MIEJSCA = {
                MIEJSCE_ZAJETE: "rezerwacja_obok_miejsca_juz_zajetego",
                MIEJSCE_WSKAZANE: "rezerwacja_miejsca_wskazanego",
                SEKCJA_WAGON: "tr_rezerwacja_obok_miejsca_juz_zajetego_wagon",
                SEKCJA_MIEJSCE: "tr_rezerwacja_obok_miejsca_juz_zajetego_miejsce"
            };

            $.each(elementyAktywneIds, function (key, elem) {

                var odcinek_1 = $("#" + elem);
                var odcinek_2 = $("#" + elem + suffix_2);

                if (ustawicPierwszyOdcinek) {
                    odcinek_1.show();
                    odcinek_2.hide();
                } else {
                    odcinek_1.hide();
                    odcinek_2.show();
                }
            });

            if (!ustawicPierwszyOdcinek) {
                $("#" + MIEJSCA.SEKCJA_WAGON).addClass("display-hide-important");
                $("#" + MIEJSCA.SEKCJA_MIEJSCE).addClass("display-hide-important");
            } else {
                $("#" + MIEJSCA.SEKCJA_WAGON).removeClass("display-hide-important");
                $("#" + MIEJSCA.SEKCJA_MIEJSCE).removeClass("display-hide-important");
            }

            var id_przesiadka = (!ustawicPierwszyOdcinek) ? suffix_2 : "";

            var miejsce_zajete = $("#" + MIEJSCA.MIEJSCE_ZAJETE + id_przesiadka);
            var miejsce_wskazane = $("#" + MIEJSCA.MIEJSCE_WSKAZANE + id_przesiadka);
            var sekcja_wagon = $("#" + MIEJSCA.SEKCJA_WAGON + id_przesiadka);
            var sekcja_miejsce = $("#" + MIEJSCA.SEKCJA_MIEJSCE + id_przesiadka);

            if (miejsce_zajete.is(":checked") || miejsce_wskazane.is(":checked")) {

                sekcja_wagon.show();
                sekcja_miejsce.show();
            } else {
                sekcja_wagon.hide();
                sekcja_miejsce.hide();

            }

        }


        function _pokazUkryjElementyDlaPrzesiadek(elementy, czyPokazac) {

            $.each(elementy, function (idx, element) {
                $.each(element, function (idxSub, elemSub) {
                    var elem = (idx == "id") ? $("#" + elemSub) : $("." + elemSub);
                    if (czyPokazac) {
                        elem.removeClass("przesiadka_hide_elem");
                    } else {
                        elem.addClass("przesiadka_hide_elem");
                    }
                });
            });
        }


    }
    ;

    function eventBlurMiejsceZajeteWskazane() {

        var elementy = ["numer_wagonu", "numer_miejsca", "numer_wagonu_2", "numer_miejsca_2"];

        $.each(elementy, function (idx, elem) {

            $("#" + elem).blur(function () {

                var self = $(this);
                var error = false;

                if (self.val().length > 0) {
                    if (!self.val().match(/^\d+$/)) {
                        self.addClass("error_input").closest(".form_wrapper_input").find(".error_info_wskazane_zajete").removeClass("display-hide");
                    } else {
                        self.removeClass("error_input").closest(".form_wrapper_input").find(".error_info_wskazane_zajete").addClass("display-hide");
                    }
                }

                /*
                 $(".error_info_wskazane_zajete").each(function(idx, elem) {
                 if($(elem).is(":visible")) {
                 error = true;
                 }
                 });                    
                 
                 if(error) {                        
                 $(".dalej_button").addClass("disabled_button");  
                 }else {                        
                 $(".dalej_button").removeClass("disabled_button");                        
                 }
                 */

            });
        });
    }

    function BilDodatkoweService() {

        function czyZaznaczonoKuszetkeSypialne() {
            return (parseInt($(".rodzaj_miejsca:checked").val()) > 1);
        }

        function czyNieWybranoCalegoPrzedzialuDlaPsa() {

            var flag = false;

            if (czyZaznaczonoKuszetkeSypialne() && czyWybranoPsa()) {

                var przedzial_ilosc = parseInt($("#przedzial").val());
                var lLozek = $("#llozek");

                var zbiorczaLiczbaOsob = getZbiorczaIloscOsob();

                if (zbiorczaLiczbaOsob < przedzial_ilosc) {
                    flag = true;

                } else if (lLozek.is(":visible") && (parseInt(lLozek.val()) < zbiorczaLiczbaOsob)) {
                    flag = true;
                }

            }

            return flag;
        }

        function getZbiorczaIloscOsob() {

            var liczba_n = $("#liczba_n");
            var liczba_osob = 0;

            var liczba_u_arr = ["liczba_u", "liczba_u_2", "liczba_u_3"];
            var kod_znizki_arr = ["kod_znizki", "kod_znizki_2", "kod_znizki_3"];

            liczba_osob = parseInt(liczba_n.val());

            $.each(liczba_u_arr, function (idx, liczba_) {
                liczba_osob += parseInt($("#" + liczba_).val());
            });

            return liczba_osob;

        }

        function czyWybranoPsa() {

            var isPies = false;
            var bil_dod_psy_arr = [17, 18, 19]; // psa, psa-asystenta, psa-przewodnika

            $(".bilet_dodatkowy").each(function (idx, elem) {
                if (bil_dod_psy_arr.indexOf(parseInt($(elem).val())) > -1) {
                    isPies = true;
                }
            });

            return isPies;
        }

        return  {
            czyNieWybranoCalegoPrzedzialuDlaPsa: czyNieWybranoCalegoPrzedzialuDlaPsa
        }

    } // end BilDodatkoweService


    function OknoModalneService() {

        this.dalejModalAtention = function () {
            $("#dalej_modal_footer").show();
            $('#dalej_modal_pracownik_kolei').hide();
            $('#dalej_modal_kolejarz_przesiadka').show();
            $("#dalej_modal_inform").show();
            $("#dalej_modal_false").hide();
            $("#dalej_modal_ok").hide();
            $("#dalej_modal_header_informacja").hide();
            $("#dalej_modal_header_uwaga").show();
        }

        this.dalejModalBiletPiesCalyPrzedzial = function () {

            $("#dalej_modal_footer").show();
            $("#dalej_modal_pies_caly_przedzial").show();
            $("#dalej_modal_ok").val($("#dalej_modal_ok").attr("v4"));
            $("#dalej_modal_inform").hide();
            $("#dalej_modal_false").hide();
            $("#dalej_modal_ok").attr("type", "button");
            $("#dalej_modal_ok").addClass("js-modal-close");
            $("#dalej_modal_header_informacja").show();
            $("#dalej_modal_header_uwaga").hide();

        }

        this.dalejModalJednoLozkoDzieckoOpiekun = function () {
            ZakupBiletuUtil().showOkienkoModalne(this, "dalej_modal_wspolne_usytuowanie_lozko_dziecko_opiekun");
        }


        this.dalejModalFalse = function () {

            $("#dalej_modal_footer").show();
            $("#dalej_modal_inform").hide();
            $("#dalej_modal_false").show();
            $("#dalej_modal_ok").attr("type", "submit");
            $("#dalej_modal_ok").removeClass("js-modal-close");
            $("#dalej_modal_header_informacja").show();
            $("#dalej_modal_header_uwaga").hide();
        }

        this.dalejModalDefault = function () {

            $("#dalej_modal_inform").hide();
            $("#dalej_modal_false").hide();
            $("#dalej_modal_ok").attr("type", "button");
            $("#dalej_modal_ok").addClass("js-modal-close");
            $("#dalej_modal_header_informacja").show();
            $("#dalej_modal_header_uwaga").hide();
        }

    }

    function init() {
        eventBlurMiejsceZajeteWskazane();
    }

    return {
        init: init
    }
};

 function ZakupBiletuUtil() {
    
     var usluga = {DO_SIEDZENIA:1, KUSZETKA:2, SYPIALNE:4 };
    
    function odblokujZablokujWieleZnizekDlaWLBC() {
                
        var SIEDZACE = 1;
        
        var tr_kod_znizki_2 = $("#tr_kod_znizki_2");        
        var znizki_sekcja_wlbc = $(".znizki_sekcja_wlbc");
        var rodzaj_miejsca_val = $(".rodzaj_miejsca").filter(':checked').val();        
        
        if(tr_kod_znizki_2.hasClass("znizki_sekcja_wlbc")) {            
            if(rodzaj_miejsca_val > SIEDZACE) {                              
                znizki_sekcja_wlbc.attr('style','display: none !important');
                wyczyscPolaOsobUlgoweKodyZnizek();
            }else {                               
                znizki_sekcja_wlbc.attr('style','display: table-row !important');
            }                        
        }
    }
    
    function wyczyscPolaOsobUlgoweKodyZnizek() {
        
        var setDefaultValue = function(elements) {            
            $.each(elements, function(idx, elem) {                
                var select = $("#" + elem);
                if(select.length > 0) {
                    select.val(select.find("option:first").val());
                }                
            });            
        }
        
        var liczba_arr = ["liczba_u_2", "liczba_u_3", "liczba_u_2_2", "liczba_u_2_3"];        
        var kod_znizki_arr = ["kod_znizki_2", "kod_znizki_3", "kod_znizki_2_2", "kod_znizki_2_3"];
        
        setDefaultValue(liczba_arr);
        setDefaultValue(kod_znizki_arr);
        
    }
    
    function showOkienkoModalne(input_ref, modal_id) {
              
        $("#"+modal_id).show();
        $("#dalej_modal_ok").val("Potwierdzam");
        $("#dalej_modal_footer").show();                        
        $("#dalej_modal_inform").hide();
        $("#dalej_modal_false").show();                        
        $("#dalej_modal_ok").attr("type","submit");                        
        $("#dalej_modal_ok").addClass("js-modal-close").click(function(event) {                        
            $(input_ref).okienkoModalne().close();                                 
        });

        $(input_ref).okienkoModalne().open();                               

    }
    
    function ustawLiczbeNJesliNieWybranoZnizkiWymiana() {
        
        var BEZ_ZNIZKI = 1;
        
        var wymiana_container = $("#wymiana_container");
        
        var liczba_n = $("#liczba_n");
        var znizki_arr = ["kod_znizki", "kod_znizki_2", "kod_znizki_3"];
        
        var czyWybranoZnizke = false;
        
        if(wymiana_container.is(":visible")) {
         
            $.each(znizki_arr, function(idx, elem) {            
                var znizka_val = parseInt($("#" + elem).val());

                if(znizka_val > BEZ_ZNIZKI) {
                    czyWybranoZnizke = true;
                }

            });

            if(parseInt(liczba_n.val()) == 0 && !czyWybranoZnizke) {
                liczba_n.val(1);
            }            
        }
        
    }
    
    function ustawMaxLiczbeLozekDlaPrzedzialu() {
        
        var llozekSelect = $('#llozek');
        
        if(llozekSelect.is(":visible")) {
          
            var ilosc_osob_w_przedziale = getIloscOsobDlaPrzedzialu();
            
            // resetujemy combo 
            llozekSelect.empty();
            
            llozekSelect.append($('<option>', {
                value: 0,
                text: Language.get('wybierz')
            }));
            
            for(var i=0; i < ilosc_osob_w_przedziale; i++ ) {                 
                 llozekSelect.append($('<option>', { 
                    value: i + 1,
                    text : i + 1 
                }));
            }
        }
        
        liczba_lozek();        
        
      }
      
      function getIloscOsobDlaPrzedzialu() {
          
           var getPrzedzialOsoby = function(przedzial_str) {
            
            var DEFAULT_VAL = 6;
            
            var ilosc = DEFAULT_VAL;			
            var regex = /[+-]?\d+(?:\.\d+)?/g;				
            var match;
            while (match = regex.exec(przedzial_str)) {
              ilosc = match[0];				  
              break;
            }
            
            return ilosc;            
        }
        
        var zaznaczona_usluga = parseInt($(".rodzaj_miejsca").filter(':checked').val()); 
        var przedzial = (zaznaczona_usluga == usluga.KUSZETKA) ? $("#klasa_wagonu") : $("#przedzial");
        var comboText = przedzial.find("option:selected").text();
        
        return getPrzedzialOsoby(comboText);
          
      }
      
      function ustawKlasePrzedzial(przedzial) {
          
          var wybranaUsluga = parseInt($(".rodzaj_miejsca:checked").val());
          
          var ustawWybranaOpcje = function(comboList) {
              
              comboList.find("option").each(function(idx, elem) {
                  
                  if($(elem).text().toLowerCase().indexOf(przedzial.toLowerCase()) != -1) {                      
                     $(elem).attr('selected', 'selected');
                  }
              });
          }
          
          if(wybranaUsluga == usluga.KUSZETKA) {              
              ustawWybranaOpcje($("#klasa_wagonu"));
              
          }else if(wybranaUsluga == usluga.SYPIALNE) {
              ustawWybranaOpcje($("#przedzial"));
              
          }          
          
      }
    
    
    return {
        odblokujZablokujWieleZnizekDlaWLBC:odblokujZablokujWieleZnizekDlaWLBC,
        showOkienkoModalne:showOkienkoModalne,
        ustawLiczbeNJesliNieWybranoZnizkiWymiana:ustawLiczbeNJesliNieWybranoZnizkiWymiana,
        ustawMaxLiczbeLozekDlaPrzedzialu:ustawMaxLiczbeLozekDlaPrzedzialu,
        ustawKlasePrzedzial:ustawKlasePrzedzial,
        getIloscOsobDlaPrzedzialu:getIloscOsobDlaPrzedzialu
    }
    
    
    
};
