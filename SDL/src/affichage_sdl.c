#include "memo_rpg.h" 
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string.h>

// --- DIMENSIONS DE LA FENÊTRE ---
#define SCREEN_WIDTH 912
#define SCREEN_HEIGHT 497

// --- DÉFINITION DES ÉTATS (ÉCRANS) DU JEU ---
#define ECRAN_ACCUEIL 0
#define ECRAN_MENU 1
#define ECRAN_SELECTION_NB_JOUEURS 2 
#define ECRAN_HOF 3
#define ECRAN_SELECTION_PERSO 4      
#define ECRAN_SAISIE_PSEUDO 5        
#define ECRAN_JEU 6
#define ECRAN_CHOIX_ARME 7 
#define ECRAN_AFFICHAGE_MONSTRE 8 
#define ECRAN_VISEUR 9 
#define ECRAN_FIN_PARTIE 10 
#define ECRAN_REGLES 11 // NOUVEL ECRAN !
#define MAX_LIGNES 30 

// =======================================================================
// FONCTION UTILITAIRE : AFFICHER UN TEXTE DANS UN BANDEAU NOIR
// =======================================================================
void afficher_bandeau_texte(SDL_Renderer* renderer, TTF_Font* police, const char* texte, int y_position) {
    SDL_Color couleurBlanche = {255, 255, 255, 255};
    
    SDL_Rect bandeau = {150, y_position - 5, 612, 40}; 
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);    
    SDL_RenderFillRect(renderer, &bandeau);
    
    SDL_Surface* surf_texte = TTF_RenderUTF8_Blended(police, texte, couleurBlanche);
    if (surf_texte) {
        SDL_Texture* tex_texte = SDL_CreateTextureFromSurface(renderer, surf_texte);
        SDL_Rect rect_texte = { (SCREEN_WIDTH/2) - (surf_texte->w/2), y_position, surf_texte->w, surf_texte->h };
        SDL_RenderCopy(renderer, tex_texte, NULL, &rect_texte); 
        SDL_FreeSurface(surf_texte);  
        SDL_DestroyTexture(tex_texte);
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
}

// =======================================================================
// FONCTION PRINCIPALE (MAIN)
// =======================================================================
int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) return 1;
    if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))) return 1;
    if (TTF_Init() == -1) {
        printf("Erreur TTF_Init: %s\n", TTF_GetError());
        return 1;
    }
    
    // --- INITIALISATION AUDIO ---
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Erreur SDL_mixer: %s\n", Mix_GetError());
    }

    SDL_Window* window = SDL_CreateWindow("Memo RPG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    SDL_Texture* imageAccueil = IMG_LoadTexture(renderer, "assets/ecran_accueil.png");
    SDL_Texture* imageSelection = IMG_LoadTexture(renderer, "assets/choix_joueur.png");
    SDL_Texture* imageSelectionNb = IMG_LoadTexture(renderer, "assets/choix_nb_joueurs.png"); 
    SDL_Texture* imageMenu = IMG_LoadTexture(renderer, "assets/menu_principal.png");
    SDL_Texture* imageHallOfFame = IMG_LoadTexture(renderer, "assets/hall_of_fame.png"); 
    SDL_Texture* imagePlateauJeu = IMG_LoadTexture(renderer, "assets/plateau.png"); 
    SDL_Texture* imageChoixArme = IMG_LoadTexture(renderer, "assets/choix_arme.png"); 
    SDL_Texture* imageRegles = IMG_LoadTexture(renderer, "assets/regles.png");
    
    SDL_Texture* imgOrc = IMG_LoadTexture(renderer, "assets/orc.png");
    SDL_Texture* imgDragon = IMG_LoadTexture(renderer, "assets/dragon.png");
    SDL_Texture* imgNazgul = IMG_LoadTexture(renderer, "assets/nazgul.png");
    SDL_Texture* imgAraignee = IMG_LoadTexture(renderer, "assets/araignee.png");
    SDL_Texture* imgTresor = IMG_LoadTexture(renderer, "assets/tresor.png");
    SDL_Texture* imgTotem = IMG_LoadTexture(renderer, "assets/totem.png");
    SDL_Texture* imgPortail = IMG_LoadTexture(renderer, "assets/portail.png");
    SDL_Texture* imageFinPartie = IMG_LoadTexture(renderer, "assets/menu_fin.png");
    
    SDL_Texture* imgBaton = IMG_LoadTexture(renderer, "assets/baton.png");
    SDL_Texture* imgArcSpe = IMG_LoadTexture(renderer, "assets/arc.png");
    SDL_Texture* imgHache = IMG_LoadTexture(renderer, "assets/hache.png");
    SDL_Texture* imgAnneau = IMG_LoadTexture(renderer, "assets/anneau.png");

    // --- Chargement des 4 pions de personnages ---
    SDL_Texture* imgPionGandalf = IMG_LoadTexture(renderer, "assets/piongandalf.png");
    SDL_Texture* imgPionGollum = IMG_LoadTexture(renderer, "assets/piongolum.png");
    SDL_Texture* imgPionGimli = IMG_LoadTexture(renderer, "assets/piongimli.png");
    SDL_Texture* imgPionTauriel = IMG_LoadTexture(renderer, "assets/piontauriel.png");

    // --- Chargement des 11 tuiles carrées pour le plateau ---
    SDL_Texture* case_orc = IMG_LoadTexture(renderer, "assets/case_orc.png");
    SDL_Texture* case_dragon = IMG_LoadTexture(renderer, "assets/case_dragon.png");
    SDL_Texture* case_nazgul = IMG_LoadTexture(renderer, "assets/case_nazgul.png");
    SDL_Texture* case_araignee = IMG_LoadTexture(renderer, "assets/case_araignee.png");
    SDL_Texture* case_tresor = IMG_LoadTexture(renderer, "assets/case_tresor.png");
    SDL_Texture* case_totem = IMG_LoadTexture(renderer, "assets/case_totem.png");
    SDL_Texture* case_portail = IMG_LoadTexture(renderer, "assets/case_portail.png");
    SDL_Texture* case_baton = IMG_LoadTexture(renderer, "assets/case_baton.png");
    SDL_Texture* case_arc = IMG_LoadTexture(renderer, "assets/case_arc.png");
    SDL_Texture* case_hache = IMG_LoadTexture(renderer, "assets/case_hache.png");
    SDL_Texture* case_anneau = IMG_LoadTexture(renderer, "assets/case_anneau.png");

    TTF_Font* police = TTF_OpenFont("assets/police.ttf", 24);
    if (!police) {
        printf("Erreur police: %s\n", TTF_GetError());
        return 1;
    }
    SDL_Color couleurTexte = {40, 20, 10, 255}; 
    SDL_Color couleurBlanche = {255, 255, 255, 255}; 

    SDL_Rect rects_nb_joueurs[3] = {
        { 101, 180, 212, 198}, 
        { 349, 179, 212, 198 }, 
        { 600, 180, 212, 198 }  
    };

    SDL_Rect rects_persos[4] = {
        { 0, 0, 228, 497 },   
        { 228, 0, 228, 497 }, 
        { 456, 0, 228, 497 }, 
        { 684, 0, 228, 497 }  
    };

    SDL_Rect rects_fin[3] = {
        { 62, 412, 253, 80 }, 
        { 330, 412, 253, 80 }, 
        { 599, 412, 253, 80 }  
    };

    SDL_Rect cases_ecran[7][7]; 
    int taille_case_w = 71;  
    int taille_case_h = 70;  
    float grille_offset_x = 198.5; 
    float grille_offset_y = -5.5;   

    for (int lig = 0; lig < 7; lig++) {
        for (int col = 0; col < 7; col++) {
            cases_ecran[lig][col].x = grille_offset_x + (col * taille_case_w) + (col * 3);  
            cases_ecran[lig][col].y = grille_offset_y + (lig * taille_case_h) + (lig * 3); 
            cases_ecran[lig][col].w = taille_case_w; 
            cases_ecran[lig][col].h = taille_case_h;
        }
    }

    // --- GESTION DU HALL OF FAME PROPRE (EN COLONNES) ---
    StatJoueur mesStats[MAX_LIGNES];
    int nbLignesLues = charger_stats(mesStats, MAX_LIGNES); 
    
    SDL_Texture *tex_nom[MAX_LIGNES], *tex_part[MAX_LIGNES], *tex_v[MAX_LIGNES], *tex_d[MAX_LIGNES], *tex_m[MAX_LIGNES];
    SDL_Rect r_nom[MAX_LIGNES], r_part[MAX_LIGNES], r_v[MAX_LIGNES], r_d[MAX_LIGNES], r_m[MAX_LIGNES];

    for (int i = 0; i < nbLignesLues; i++) {
        char str_part[10], str_v[10], str_d[10], str_m[10];
        sprintf(str_part, "%d", mesStats[i].parties);
        sprintf(str_v, "%d", mesStats[i].victoires);
        sprintf(str_d, "%d", mesStats[i].defaites);
        sprintf(str_m, "%d", mesStats[i].nmb_mort);

        SDL_Surface* s_nom = TTF_RenderUTF8_Blended(police, mesStats[i].nom, couleurTexte);
        SDL_Surface* s_part = TTF_RenderUTF8_Blended(police, str_part, couleurTexte);
        SDL_Surface* s_v = TTF_RenderUTF8_Blended(police, str_v, couleurTexte);
        SDL_Surface* s_d = TTF_RenderUTF8_Blended(police, str_d, couleurTexte);
        SDL_Surface* s_m = TTF_RenderUTF8_Blended(police, str_m, couleurTexte);

        tex_nom[i] = SDL_CreateTextureFromSurface(renderer, s_nom);
        tex_part[i] = SDL_CreateTextureFromSurface(renderer, s_part);
        tex_v[i] = SDL_CreateTextureFromSurface(renderer, s_v);
        tex_d[i] = SDL_CreateTextureFromSurface(renderer, s_d);
        tex_m[i] = SDL_CreateTextureFromSurface(renderer, s_m);

        int y_base = 210 + (i * 35); 
        r_nom[i]  = (SDL_Rect){ 225, y_base, s_nom->w, s_nom->h };  
        r_part[i] = (SDL_Rect){ 460, y_base, s_part->w, s_part->h };
        r_v[i]    = (SDL_Rect){ 548, y_base, s_v->w, s_v->h };      
        r_d[i]    = (SDL_Rect){ 598, y_base, s_d->w, s_d->h };      
        r_m[i]    = (SDL_Rect){ 635, y_base, s_m->w, s_m->h };      

        SDL_FreeSurface(s_nom); SDL_FreeSurface(s_part); SDL_FreeSurface(s_v); SDL_FreeSurface(s_d); SDL_FreeSurface(s_m);
    }
    
    Mix_Music* musiqueMenu = Mix_LoadMUS("assets/menu.mp3"); 
    Mix_Music* musiqueJeu = Mix_LoadMUS("assets/jeu.mp3");   
    
    // VOLUME 
    Mix_VolumeMusic(MIX_MAX_VOLUME / 10); 

    // On lance la musique du menu avec un "Fade In" de 2000 millisecondes (2 secondes)
    if (musiqueMenu != NULL) {
        Mix_FadeInMusic(musiqueMenu, -1, 2000); 
    }

    int scrollY = 0; 
    SDL_Rect zoneParchemin = {150, 200, 610, 260}; 

    int running = 1;
    SDL_Event event;
    int ecranActuel = ECRAN_ACCUEIL; 
    
    int nombreDeJoueurs = 0;
    int joueur_en_cours = 0;
    int dejas_pris[4] = {0, 0, 0, 0}; 
    char pseudo_temp[11] = ""; 
    Personnage joueurs[4]; 
    Plateau monPlateau;

    int curseur_nb = 0;    
    int curseur_perso = 0; 
    int curseur_arme = 0; 
    int curseur_fin = 0; 
    int viseur_lig = 3, viseur_col = 3; 
    
    SDL_Texture* texturePseudo = NULL;
    SDL_Rect rectPseudo = {0, 0, 0, 0};

    while (running==1) {
        
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = 0;

            if (event.type == SDL_TEXTINPUT && ecranActuel == ECRAN_SAISIE_PSEUDO) {
                if (strlen(pseudo_temp) < 10) {
                    strcat(pseudo_temp, event.text.text);
                    if (texturePseudo != NULL) SDL_DestroyTexture(texturePseudo);
                    SDL_Surface* surf = TTF_RenderUTF8_Blended(police, pseudo_temp, couleurBlanche);
                    texturePseudo = SDL_CreateTextureFromSurface(renderer, surf);
                    
                    rectPseudo.w = surf->w;
                    rectPseudo.h = surf->h;
                    rectPseudo.x = rects_persos[curseur_perso].x + (114 - surf->w/2); 
                    rectPseudo.y = 420; 
                    SDL_FreeSurface(surf);
                }
            }

            if (event.type == SDL_KEYDOWN) {
                int lancerTransition = 0; 
                int ecranSuivant = ECRAN_ACCUEIL;

                if (ecranActuel == ECRAN_ACCUEIL) {
                    if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_SPACE) {
                        lancerTransition = 1; ecranSuivant = ECRAN_MENU;
                    }
                } 
                else if (ecranActuel == ECRAN_MENU) {
                    if (event.key.keysym.sym == SDLK_1 || event.key.keysym.sym == SDLK_KP_1) {
                        lancerTransition = 1; ecranSuivant = ECRAN_SELECTION_NB_JOUEURS;
                    }
                    else if (event.key.keysym.sym == SDLK_2 || event.key.keysym.sym == SDLK_KP_2) {
                        lancerTransition = 1; ecranSuivant = ECRAN_HOF;
                    }
                    else if (event.key.keysym.sym == SDLK_3 || event.key.keysym.sym == SDLK_KP_3) {
                        running = 0; 
                    }
                } 
                else if (ecranActuel == ECRAN_HOF) {
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        lancerTransition = 1; ecranSuivant = ECRAN_MENU; scrollY = 0; 
                    }
                    else if (event.key.keysym.sym == SDLK_UP) { scrollY += 30; if (scrollY > 0) scrollY = 0; } 
                    else if (event.key.keysym.sym == SDLK_DOWN) { 
                        int hauteurTotaleTexte = nbLignesLues * 35;
                        int limiteBasse = hauteurTotaleTexte - zoneParchemin.h;
                        if (limiteBasse < 0) limiteBasse = 0; 
                        scrollY -= 30; 
                        if (scrollY < -limiteBasse) scrollY = -limiteBasse;
                    }
                }
                else if (ecranActuel == ECRAN_SELECTION_NB_JOUEURS) {
                    if (event.key.keysym.sym == SDLK_ESCAPE) { lancerTransition = 1; ecranSuivant = ECRAN_MENU; }
                    else if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_q) {
                        curseur_nb--; if (curseur_nb < 0) curseur_nb = 2; 
                    }
                    else if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d) {
                        curseur_nb++; if (curseur_nb > 2) curseur_nb = 0;
                    }
                    else if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER) {
                        nombreDeJoueurs = curseur_nb + 2; 
                        joueur_en_cours = 0;
                        curseur_perso = 0;
                        ecranActuel = ECRAN_SELECTION_PERSO; 
                    }
                }
                else if (ecranActuel == ECRAN_SELECTION_PERSO) {
                    if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_q) {
                        curseur_perso--; if (curseur_perso < 0) curseur_perso = 3;
                    }
                    else if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d) {
                        curseur_perso++; if (curseur_perso > 3) curseur_perso = 0;
                    }
                    else if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER) {
                        int mapping[] = {GANDALF, GOLLUM, TAURIEL, GIMLI}; 
                        int classe_choisie = mapping[curseur_perso];
                        
                        if (dejas_pris[classe_choisie] == 0) {
                            dejas_pris[classe_choisie] = 1;
                            joueurs[joueur_en_cours].perso = (Classe)classe_choisie;
                            pseudo_temp[0] = '\0';
                            if (texturePseudo != NULL) { SDL_DestroyTexture(texturePseudo); texturePseudo = NULL; }
                            SDL_StartTextInput(); 
                            ecranActuel = ECRAN_SAISIE_PSEUDO;
                        }
                    }
                }
                else if (ecranActuel == ECRAN_SAISIE_PSEUDO) {
                    if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER) {
                        if (strlen(pseudo_temp) > 0) {
                            strcpy(joueurs[joueur_en_cours].nomJoueur, pseudo_temp);
                            SDL_StopTextInput();
                            joueur_en_cours++;
                            
                            if (joueur_en_cours < nombreDeJoueurs) {
                                ecranActuel = ECRAN_SELECTION_PERSO;
                            } else {
                                // --- Les persos sont choisis, on lance le fondu vers les règles ! ---
                                lancerTransition = 1;
                                ecranSuivant = ECRAN_REGLES;
                            }
                        }
                    }
                    else if (event.key.keysym.sym == SDLK_BACKSPACE && strlen(pseudo_temp) > 0) {
                        pseudo_temp[strlen(pseudo_temp) - 1] = '\0';
                        if (texturePseudo != NULL) SDL_DestroyTexture(texturePseudo);
                        if (strlen(pseudo_temp) > 0) {
                            SDL_Surface* surf = TTF_RenderUTF8_Blended(police, pseudo_temp, couleurBlanche);
                            texturePseudo = SDL_CreateTextureFromSurface(renderer, surf);
                            rectPseudo.w = surf->w;
                            rectPseudo.h = surf->h;
                            rectPseudo.x = rects_persos[curseur_perso].x + (114 - surf->w/2);
                            SDL_FreeSurface(surf);
                        } else {
                            texturePseudo = NULL;
                        }
                    }
                }
                else if (ecranActuel == ECRAN_REGLES) {
                    // --- NOUVEAU : ECRAN DES RÈGLES ---
                    if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER || event.key.keysym.sym == SDLK_SPACE) {
                        
                        printf("\n--- LA PARTIE COMMENCE ---\n");
                        
                        // ==========================================
                        // TRANSITION AUDIO ET VISUELLE ULTRA STYLÉE
                        // ==========================================
                        Mix_FadeOutMusic(1000); // 1. La musique baisse progressivement sur 1 seconde
                        
                        // 2. On affiche un écran noir pour masquer les règles pendant le silence
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                        SDL_RenderClear(renderer);
                        afficher_bandeau_texte(renderer, police, "Preparation de la partie...", 240);
                        SDL_RenderPresent(renderer);
                        
                        SDL_Delay(1000); // On attend que la musique 1 finisse de s'éteindre
                        SDL_Delay(3000); // 3. SILENCE TOTAL pendant 3 secondes (Suspense !)
                        
                        // On initialise le jeu en arrière-plan pendant le silence
                        monPlateau = initialisation(joueurs, nombreDeJoueurs);
                        depart(joueurs, nombreDeJoueurs); 
                        joueur_en_cours = 0; 
                        
                        // 4. On lance la nouvelle musique avec une montée progressive sur 2 secondes
                        if (musiqueJeu != NULL) Mix_FadeInMusic(musiqueJeu, -1, 2000);
                        
                        ecranActuel = ECRAN_JEU; 
                    }
                }
                else if (ecranActuel == ECRAN_JEU) {
                    
                    // --- VÉRIFICATION DU BLOCAGE (Si encerclé) ---
                    if (verifcaselibre(&monPlateau, joueurs[joueur_en_cours].colonne, joueurs[joueur_en_cours].ligne - 1) == 0 &&
                        verifcaselibre(&monPlateau, joueurs[joueur_en_cours].colonne, joueurs[joueur_en_cours].ligne + 1) == 0 &&
                        verifcaselibre(&monPlateau, joueurs[joueur_en_cours].colonne + 1, joueurs[joueur_en_cours].ligne) == 0 &&
                        verifcaselibre(&monPlateau, joueurs[joueur_en_cours].colonne - 1, joueurs[joueur_en_cours].ligne) == 0) {
                        
                        printf("\n[BLOQUE] %s n'a plus aucune case cachee accessible ! Fin du tour.\n", joueurs[joueur_en_cours].nomJoueur);
                        
                        // On ferme le plateau et on remet le joueur sur sa case de spawn
                        reset_tableau(&joueurs[joueur_en_cours], &monPlateau); 
                        
                        // On passe au joueur suivant
                        joueur_en_cours++;
                        if (joueur_en_cours >= nombreDeJoueurs) joueur_en_cours = 0;
                        
                        continue; // On arrête là, on ne traite pas le mouvement !
                    }

                    // --- MOUVEMENT NORMAL ---
                    int future_ligne = joueurs[joueur_en_cours].ligne;
                    int future_colonne = joueurs[joueur_en_cours].colonne;
                    int a_bouge = 0;

                    if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_z) { future_ligne--; a_bouge = 1; }
                    else if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s) { future_ligne++; a_bouge = 1; }
                    else if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_q) { future_colonne--; a_bouge = 1; }
                    else if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d) { future_colonne++; a_bouge = 1; }

                    if (a_bouge == 1) {
                        if (verifcaselibre(&monPlateau, future_colonne, future_ligne) == 1) {
                            joueurs[joueur_en_cours].ligne = future_ligne;
                            joueurs[joueur_en_cours].colonne = future_colonne;
                            
                            curseur_arme = 0; 
                            ecranActuel = ECRAN_CHOIX_ARME; 
                        } else {
                            printf("-> Mur ou case deja fouillee !\n");
                        }
                    }
                }
                else if (ecranActuel == ECRAN_CHOIX_ARME) {
                    if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_q) {
                        curseur_arme--; if (curseur_arme < 0) curseur_arme = 3;
                    }
                    else if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d) {
                        curseur_arme++; if (curseur_arme > 3) curseur_arme = 0;
                    }
                    else if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER) {
                        int mapping_armes[] = {BDF, EPEE, ARC, LANCE}; 
                        joueurs[joueur_en_cours].arme_actuelle = mapping_armes[curseur_arme];
                        
                        monPlateau.tableau[joueurs[joueur_en_cours].ligne][joueurs[joueur_en_cours].colonne].est_decouverte = 1;
                        ecranActuel = ECRAN_AFFICHAGE_MONSTRE; 
                    }
                }
                else if (ecranActuel == ECRAN_AFFICHAGE_MONSTRE) {
                    if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER || event.key.keysym.sym == SDLK_SPACE) {
                        
                        Type_case t = monPlateau.tableau[joueurs[joueur_en_cours].ligne][joueurs[joueur_en_cours].colonne].type;
                        
                        if (t == TOTEM || t == PORTAIL) {
                            viseur_lig = 3; viseur_col = 3; 
                            ecranActuel = ECRAN_VISEUR;
                        } 
                        else {
                            int mort = resolution_case(&joueurs[joueur_en_cours], &monPlateau, 0, 0);
                            
                            if (joueurs[joueur_en_cours].aLeTresor == 1 && joueurs[joueur_en_cours].aLarme == 1) {
                                printf("\n!!! VICTOIRE !!! %s a gagne la partie !\n", joueurs[joueur_en_cours].nomJoueur);
                                mettre_a_jour_stats(joueurs[joueur_en_cours].nomJoueur, 1, 0, 0);
                                for (int k = 0; k < nombreDeJoueurs; k++) {
                                    if (k != joueur_en_cours) mettre_a_jour_stats(joueurs[k].nomJoueur, 0, 1, 0);
                                }
                                
                                curseur_fin = 0; 
                                ecranActuel = ECRAN_FIN_PARTIE; 
                            } else {
                                if (mort == 1) {
                                    joueur_en_cours++;
                                    if (joueur_en_cours >= nombreDeJoueurs) joueur_en_cours = 0; 
                                }
                                ecranActuel = ECRAN_JEU; 
                            }
                        }
                    }
                }
                else if (ecranActuel == ECRAN_VISEUR) {
                    if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_z) { if (viseur_lig > 1) viseur_lig--; }
                    else if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s) { if (viseur_lig < 5) viseur_lig++; }
                    else if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_q) { if (viseur_col > 1) viseur_col--; }
                    else if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d) { if (viseur_col < 5) viseur_col++; }
                    else if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER) {
                        Type_case type_c = monPlateau.tableau[joueurs[joueur_en_cours].ligne][joueurs[joueur_en_cours].colonne].type;
                        int valid = 1;
                        
                        if (type_c == TOTEM && monPlateau.tableau[viseur_lig][viseur_col].est_decouverte == 1) {
                            valid = 0;
                            printf("-> Pour le Totem, il faut choisir une case qui n'a pas encore ete fouillee !\n");
                        }
                        
                        if (valid == 1) {
                            if (type_c == TOTEM) {
                                printf("\nVous etes tombe sur un Totem ! La magie opère...\n");
                                Type_case temp_type = monPlateau.tableau[viseur_lig][viseur_col].type;
                                int temp_prop = monPlateau.tableau[viseur_lig][viseur_col].proprietaire;
                                
                                monPlateau.tableau[viseur_lig][viseur_col].type = monPlateau.tableau[joueurs[joueur_en_cours].ligne][joueurs[joueur_en_cours].colonne].type;
                                monPlateau.tableau[viseur_lig][viseur_col].proprietaire = monPlateau.tableau[joueurs[joueur_en_cours].ligne][joueurs[joueur_en_cours].colonne].proprietaire;
                                
                                monPlateau.tableau[joueurs[joueur_en_cours].ligne][joueurs[joueur_en_cours].colonne].type = temp_type;
                                monPlateau.tableau[joueurs[joueur_en_cours].ligne][joueurs[joueur_en_cours].colonne].proprietaire = temp_prop;
                                printf("Les cases ont ete permutees !\n");
                            } 
                            else if (type_c == PORTAIL) {
                                printf("\nUn portail de teleportation ! Vouuuuh ! Teleportation en [%d][%d] !\n", viseur_lig, viseur_col);
                                joueurs[joueur_en_cours].ligne = viseur_lig;
                                joueurs[joueur_en_cours].colonne = viseur_col;
                                monPlateau.tableau[viseur_lig][viseur_col].est_decouverte = 1;
                            }
                            
                            ecranActuel = ECRAN_AFFICHAGE_MONSTRE; 
                        }
                    }
                }
                else if (ecranActuel == ECRAN_FIN_PARTIE) {
                    if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_q) {
                        curseur_fin--; if (curseur_fin < 0) curseur_fin = 2;
                    }
                    else if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d) {
                        curseur_fin++; if (curseur_fin > 2) curseur_fin = 0;
                    }
                    else if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER) {
                        
                        if (curseur_fin == 0) {
                            // 1er bouton (Rejouer mêmes persos) : Transition visuelle classique rapide
                            lancerTransition = 1; 
                            Mix_FadeOutMusic(800); 
                            
                            monPlateau = initialisation(joueurs, nombreDeJoueurs);
                            depart(joueurs, nombreDeJoueurs);
                            joueur_en_cours = 0;
                            
                            if (musiqueJeu != NULL) Mix_FadeInMusic(musiqueJeu, -1, 1500); 
                            ecranSuivant = ECRAN_JEU; 
                        }
                        else {
                            // 2ème et 3ème boutons : La fameuse transition dramatique !
                            Mix_FadeOutMusic(1000); // On baisse la musique de victoire/jeu
                            
                            // On affiche un écran tout noir
                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                            SDL_RenderClear(renderer);
                            
                            // On adapte le texte selon le bouton choisi
                            if (curseur_fin == 1) {
                                afficher_bandeau_texte(renderer, police, "Retour a l'auberge...", 240);
                            } else if (curseur_fin == 2) {
                                afficher_bandeau_texte(renderer, police, "Retour au menu principal...", 240);
                            }
                            SDL_RenderPresent(renderer);
                            
                            // Le suspense...
                            SDL_Delay(1000); // Attend la fin du fondu audio
                            SDL_Delay(2000); // 2 secondes de silence apaisant
                            
                            // On relance la musique du Menu
                            if (musiqueMenu != NULL) Mix_FadeInMusic(musiqueMenu, -1, 2000);
                            
                            // On réinitialise les variables et on change d'écran
                            if (curseur_fin == 1) {
                                for(int k=0; k<4; k++) dejas_pris[k] = 0; 
                                ecranActuel = ECRAN_SELECTION_NB_JOUEURS;
                            } else {
                                nombreDeJoueurs = 0;
                                for(int k=0; k<4; k++) dejas_pris[k] = 0; 
                                ecranActuel = ECRAN_MENU;
                            }
                        }
                    }
                }

                // ============ EFFET DE TRANSITION (FONDU AU NOIR) ============
                if (lancerTransition == 1) {
                    for (int alpha = 0; alpha <= 255; alpha += 15) {
                        SDL_RenderClear(renderer);
                        if (ecranActuel == ECRAN_ACCUEIL) {
                            SDL_RenderCopy(renderer, imageAccueil, NULL, NULL);
                        }
                        else if(ecranActuel == ECRAN_MENU) {
                            SDL_RenderCopy(renderer, imageMenu, NULL, NULL);
                            afficher_bandeau_texte(renderer, police, "Selectionner [1],[2] ou [3]", 424);
                        }
                        else if(ecranActuel == ECRAN_SELECTION_NB_JOUEURS) SDL_RenderCopy(renderer, imageSelectionNb, NULL, NULL);
                        else if(ecranActuel == ECRAN_HOF) {
                            SDL_RenderCopy(renderer, imageHallOfFame, NULL, NULL);
                            SDL_RenderSetClipRect(renderer, &zoneParchemin); 
                            for (int i = 0; i < nbLignesLues; i++) {
                                SDL_Rect aff_nom = r_nom[i];   aff_nom.y += scrollY;
                                SDL_Rect aff_part = r_part[i]; aff_part.y += scrollY;
                                SDL_Rect aff_v = r_v[i];       aff_v.y += scrollY;
                                SDL_Rect aff_d = r_d[i];       aff_d.y += scrollY;
                                SDL_Rect aff_m = r_m[i];       aff_m.y += scrollY;
                                
                                SDL_RenderCopy(renderer, tex_nom[i], NULL, &aff_nom);
                                SDL_RenderCopy(renderer, tex_part[i], NULL, &aff_part);
                                SDL_RenderCopy(renderer, tex_v[i], NULL, &aff_v);
                                SDL_RenderCopy(renderer, tex_d[i], NULL, &aff_d);
                                SDL_RenderCopy(renderer, tex_m[i], NULL, &aff_m);
                            }
                            SDL_RenderSetClipRect(renderer, NULL); 
                        }
                        else if(ecranActuel == ECRAN_REGLES) { // --- NOUVEAU ---
                            SDL_RenderCopy(renderer, imageRegles, NULL, NULL);
                        }
                        else if(ecranActuel == ECRAN_FIN_PARTIE) {
                            SDL_RenderCopy(renderer, imageFinPartie, NULL, NULL);
                        }
                        
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, alpha);
                        SDL_RenderFillRect(renderer, NULL); 
                        SDL_RenderPresent(renderer);
                        SDL_Delay(10);
                    }
                    
                    ecranActuel = ecranSuivant; 

                    for (int alpha = 255; alpha >= 0; alpha -= 15) {
                        SDL_RenderClear(renderer);
                        if (ecranActuel == ECRAN_ACCUEIL) {
                            SDL_RenderCopy(renderer, imageAccueil, NULL, NULL);
                        }
                        else if(ecranActuel == ECRAN_MENU) {
                            SDL_RenderCopy(renderer, imageMenu, NULL, NULL);
                            afficher_bandeau_texte(renderer, police, "Selectionner [1],[2] ou [3]", 424);
                        }
                        else if(ecranActuel == ECRAN_SELECTION_NB_JOUEURS) SDL_RenderCopy(renderer, imageSelectionNb, NULL, NULL);
                        else if(ecranActuel == ECRAN_HOF) {
                            SDL_RenderCopy(renderer, imageHallOfFame, NULL, NULL);
                            SDL_RenderSetClipRect(renderer, &zoneParchemin); 
                            for (int i = 0; i < nbLignesLues; i++) {
                                SDL_Rect aff_nom = r_nom[i];   aff_nom.y += scrollY;
                                SDL_Rect aff_part = r_part[i]; aff_part.y += scrollY;
                                SDL_Rect aff_v = r_v[i];       aff_v.y += scrollY;
                                SDL_Rect aff_d = r_d[i];       aff_d.y += scrollY;
                                SDL_Rect aff_m = r_m[i];       aff_m.y += scrollY;
                                
                                SDL_RenderCopy(renderer, tex_nom[i], NULL, &aff_nom);
                                SDL_RenderCopy(renderer, tex_part[i], NULL, &aff_part);
                                SDL_RenderCopy(renderer, tex_v[i], NULL, &aff_v);
                                SDL_RenderCopy(renderer, tex_d[i], NULL, &aff_d);
                                SDL_RenderCopy(renderer, tex_m[i], NULL, &aff_m);
                            }
                            SDL_RenderSetClipRect(renderer, NULL); 
                        }
                        else if(ecranActuel == ECRAN_REGLES) { // --- NOUVEAU ---
                            SDL_RenderCopy(renderer, imageRegles, NULL, NULL);
                        }
                        else if(ecranActuel == ECRAN_FIN_PARTIE) {
                            SDL_RenderCopy(renderer, imageFinPartie, NULL, NULL);
                        }
                        
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, alpha);
                        SDL_RenderFillRect(renderer, NULL);
                        SDL_RenderPresent(renderer);
                        SDL_Delay(10);
                    }
                }
            }
        }

        // --- 2. AFFICHAGE DES IMAGES (RENDU) ---
        SDL_RenderClear(renderer);
        
        if (ecranActuel == ECRAN_ACCUEIL) {
            SDL_RenderCopy(renderer, imageAccueil, NULL, NULL);
            afficher_bandeau_texte(renderer, police, "Appuyez sur Entree pour commencer", 440);
        }
        else if (ecranActuel == ECRAN_MENU) {
            SDL_RenderCopy(renderer, imageMenu, NULL, NULL);
            afficher_bandeau_texte(renderer, police, "Selectionner [1],[2] ou [3]", 424);
        }
        else if (ecranActuel == ECRAN_HOF) {
            SDL_RenderCopy(renderer, imageHallOfFame, NULL, NULL);
            SDL_RenderSetClipRect(renderer, &zoneParchemin); 
            for (int i = 0; i < nbLignesLues; i++) {
                SDL_Rect aff_nom = r_nom[i];   aff_nom.y += scrollY;
                SDL_Rect aff_part = r_part[i]; aff_part.y += scrollY;
                SDL_Rect aff_v = r_v[i];       aff_v.y += scrollY;
                SDL_Rect aff_d = r_d[i];       aff_d.y += scrollY;
                SDL_Rect aff_m = r_m[i];       aff_m.y += scrollY;
                
                SDL_RenderCopy(renderer, tex_nom[i], NULL, &aff_nom);
                SDL_RenderCopy(renderer, tex_part[i], NULL, &aff_part);
                SDL_RenderCopy(renderer, tex_v[i], NULL, &aff_v);
                SDL_RenderCopy(renderer, tex_d[i], NULL, &aff_d);
                SDL_RenderCopy(renderer, tex_m[i], NULL, &aff_m);
            }
            SDL_RenderSetClipRect(renderer, NULL); 
        }
        else if (ecranActuel == ECRAN_SELECTION_NB_JOUEURS) {
            SDL_RenderCopy(renderer, imageSelectionNb, NULL, NULL);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);
            SDL_RenderFillRect(renderer, &rects_nb_joueurs[curseur_nb]);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
        }
        else if (ecranActuel == ECRAN_SELECTION_PERSO || ecranActuel == ECRAN_SAISIE_PSEUDO) {
            SDL_RenderCopy(renderer, imageSelection, NULL, NULL);
            
            int mapping[] = {GANDALF, GOLLUM, TAURIEL, GIMLI};
            for(int i=0; i<4; i++) {
                if(dejas_pris[mapping[i]]) {
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 150); 
                    SDL_RenderFillRect(renderer, &rects_persos[i]);
                }
            }

            if (ecranActuel == ECRAN_SELECTION_PERSO) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 120);
                SDL_RenderFillRect(renderer, &rects_persos[curseur_perso]);
            } else {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 180);
                SDL_RenderFillRect(renderer, &rects_persos[curseur_perso]);
                if (texturePseudo != NULL) SDL_RenderCopy(renderer, texturePseudo, NULL, &rectPseudo);
            }
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
            
            char texte_indication[100];
            if (ecranActuel == ECRAN_SELECTION_PERSO) {
                sprintf(texte_indication, "Joueur %d, choisissez votre personnage !", joueur_en_cours + 1);
            } else {
                sprintf(texte_indication, "Joueur %d, entrez votre pseudo :", joueur_en_cours + 1);
            }
            afficher_bandeau_texte(renderer, police, texte_indication, 25);
        }
        else if (ecranActuel == ECRAN_REGLES) { // --- NOUVEAU ---
            SDL_RenderCopy(renderer, imageRegles, NULL, NULL);
            afficher_bandeau_texte(renderer, police, "Appuyez sur Entree pour demarrer la partie !", 440);
        }

        // ==========================================
        // GESTION COMPLÈTE DU PLATEAU (Jeu + Arme + Monstre + Viseur)
        // ==========================================
        else if (ecranActuel >= ECRAN_JEU && ecranActuel <= ECRAN_FIN_PARTIE) {
            
            SDL_RenderCopy(renderer, imagePlateauJeu, NULL, NULL);

            for (int lig = 1; lig <= 5; lig++) {
                for (int col = 1; col <= 5; col++) {
                    if (monPlateau.tableau[lig][col].est_decouverte == 1) {
                        Type_case type_c = monPlateau.tableau[lig][col].type;
                        SDL_Texture* texCase = NULL;
                        
                        if (type_c == DRAGON) texCase = case_dragon;
                        else if (type_c == ORC) texCase = case_orc;
                        else if (type_c == NAZGUL) texCase = case_nazgul;
                        else if (type_c == ARAIGNEE) texCase = case_araignee;
                        else if (type_c == TRESOR) texCase = case_tresor;
                        else if (type_c == TOTEM) texCase = case_totem;
                        else if (type_c == PORTAIL) texCase = case_portail;
                        
                        else if (type_c == ARME_SPE) {
                            int proprio = monPlateau.tableau[lig][col].proprietaire;
                            if (proprio == GANDALF) texCase = case_baton;
                            else if (proprio == TAURIEL) texCase = case_arc;
                            else if (proprio == GOLLUM) texCase = case_anneau;
                            else if (proprio == GIMLI) texCase = case_hache;
                            else texCase = case_baton; 
                        }
                        
                        if (texCase != NULL) {
                            SDL_RenderCopy(renderer, texCase, NULL, &cases_ecran[lig][col]);
                        } else {
                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 150); 
                            SDL_RenderFillRect(renderer, &cases_ecran[lig][col]);
                        }
                    }
                }
            }

            if (ecranActuel == ECRAN_JEU) {
                SDL_Rect case_entiere = cases_ecran[joueurs[joueur_en_cours].ligne][joueurs[joueur_en_cours].colonne];
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);
                SDL_RenderFillRect(renderer, &case_entiere);
            }

            for (int i = 0; i < nombreDeJoueurs; i++) {
                int posCol = joueurs[i].colonne; 
                int posLig = joueurs[i].ligne;   
                
                SDL_Rect pos_pion = cases_ecran[posLig][posCol]; 
                pos_pion.x += 6; pos_pion.y += 7; pos_pion.w = 55; pos_pion.h = 55; 

                SDL_Texture* texPion = NULL;
                if (joueurs[i].perso == GANDALF) texPion = imgPionGandalf;
                else if (joueurs[i].perso == TAURIEL) texPion = imgPionTauriel;
                else if (joueurs[i].perso == GOLLUM) texPion = imgPionGollum;
                else if (joueurs[i].perso == GIMLI) texPion = imgPionGimli;
                
                if (texPion != NULL) {
                    SDL_RenderCopy(renderer, texPion, NULL, &pos_pion);
                }
            }
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 

            if (ecranActuel == ECRAN_CHOIX_ARME) {
                SDL_RenderCopy(renderer, imageChoixArme, NULL, NULL);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 120);
                SDL_RenderFillRect(renderer, &rects_persos[curseur_arme]); 
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
                
                afficher_bandeau_texte(renderer, police, "Veuillez choisir votre arme", 25);
            }
            else if (ecranActuel == ECRAN_AFFICHAGE_MONSTRE) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 150); 
                SDL_RenderFillRect(renderer, NULL);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

                Type_case type_actuel = monPlateau.tableau[joueurs[joueur_en_cours].ligne][joueurs[joueur_en_cours].colonne].type;
                SDL_Texture* texMonstre = NULL;
                
                if (type_actuel == DRAGON) texMonstre = imgDragon;
                else if (type_actuel == ORC) texMonstre = imgOrc;
                else if (type_actuel == NAZGUL) texMonstre = imgNazgul;
                else if (type_actuel == ARAIGNEE) texMonstre = imgAraignee;
                else if (type_actuel == TRESOR) texMonstre = imgTresor;
                else if (type_actuel == TOTEM) texMonstre = imgTotem;
                else if (type_actuel == PORTAIL) texMonstre = imgPortail;
                
                else if (type_actuel == ARME_SPE) {
                    int proprio = monPlateau.tableau[joueurs[joueur_en_cours].ligne][joueurs[joueur_en_cours].colonne].proprietaire;
                    if (proprio == GANDALF) texMonstre = imgBaton;
                    else if (proprio == TAURIEL) texMonstre = imgArcSpe;
                    else if (proprio == GOLLUM) texMonstre = imgAnneau;
                    else if (proprio == GIMLI) texMonstre = imgHache;
                }

                if (texMonstre != NULL) {
                    SDL_RenderCopy(renderer, texMonstre, NULL, NULL);
                }
                
                afficher_bandeau_texte(renderer, police, "Appuyez sur Entree pour continuer", 440);
            }
            else if (ecranActuel == ECRAN_VISEUR) {
                SDL_Rect r_viseur = cases_ecran[viseur_lig][viseur_col];
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); 
                SDL_RenderDrawRect(renderer, &r_viseur);
                r_viseur.x+=1; r_viseur.y+=1; r_viseur.w-=2; r_viseur.h-=2; SDL_RenderDrawRect(renderer, &r_viseur);
                r_viseur.x+=1; r_viseur.y+=1; r_viseur.w-=2; r_viseur.h-=2; SDL_RenderDrawRect(renderer, &r_viseur);
                
                afficher_bandeau_texte(renderer, police, "Deplacez le curseur ROUGE et validez la case !", 25);
            }
            
            // === ON AFFICHE LE MENU DE FIN PAR-DESSUS LE PLATEAU ===
            if (ecranActuel == ECRAN_FIN_PARTIE) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 150); 
                SDL_RenderFillRect(renderer, NULL);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                
                SDL_RenderCopy(renderer, imageFinPartie, NULL, NULL);
                
                // --- AFFICHER LE NOM DU GAGNANT ---
                char texte_victoire[100];
                sprintf(texte_victoire, "Grand Vainqueur : %s", joueurs[joueur_en_cours].nomJoueur);
                
                SDL_Surface* surf_victoire = TTF_RenderUTF8_Blended(police, texte_victoire, couleurBlanche);
                if (surf_victoire) {
                    SDL_Texture* tex_victoire = SDL_CreateTextureFromSurface(renderer, surf_victoire);
                    
                    // Centrage du texte en blanc à la hauteur Y = 147
                    SDL_Rect rect_victoire = { (SCREEN_WIDTH/2) - (surf_victoire->w/2), 147, surf_victoire->w, surf_victoire->h };
                    SDL_RenderCopy(renderer, tex_victoire, NULL, &rect_victoire);
                    
                    SDL_FreeSurface(surf_victoire);
                    SDL_DestroyTexture(tex_victoire);
                }
                
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);
                SDL_RenderFillRect(renderer, &rects_fin[curseur_fin]);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
            }
            
        } // <-- FIN DE LA GRANDE SECTION DU PLATEAU
        
        // --- 3. ACTUALISATION DE L'ÉCRAN ---
        SDL_RenderPresent(renderer);
    }

    // --- NETTOYAGE ---
    for (int i = 0; i < nbLignesLues; i++) {
        SDL_DestroyTexture(tex_nom[i]);
        SDL_DestroyTexture(tex_part[i]);
        SDL_DestroyTexture(tex_v[i]);
        SDL_DestroyTexture(tex_d[i]);
        SDL_DestroyTexture(tex_m[i]);
    }
    if (texturePseudo != NULL) SDL_DestroyTexture(texturePseudo);
    TTF_CloseFont(police);
    
    SDL_DestroyTexture(imageAccueil);
    SDL_DestroyTexture(imageMenu);
    SDL_DestroyTexture(imageSelection);
    SDL_DestroyTexture(imageSelectionNb);
    SDL_DestroyTexture(imageHallOfFame);
    SDL_DestroyTexture(imagePlateauJeu);
    SDL_DestroyTexture(imageChoixArme); 
    SDL_DestroyTexture(imageRegles); // NOUVEAU
    
    SDL_DestroyTexture(imgOrc);
    SDL_DestroyTexture(imgDragon);
    SDL_DestroyTexture(imgNazgul);
    SDL_DestroyTexture(imgAraignee);
    SDL_DestroyTexture(imgTresor);
    SDL_DestroyTexture(imgTotem);
    SDL_DestroyTexture(imgPortail);
    
    SDL_DestroyTexture(imgBaton);
    SDL_DestroyTexture(imgArcSpe);
    SDL_DestroyTexture(imgHache);
    SDL_DestroyTexture(imgAnneau);
    SDL_DestroyTexture(imageFinPartie);

    SDL_DestroyTexture(imgPionGandalf);
    SDL_DestroyTexture(imgPionGollum);
    SDL_DestroyTexture(imgPionGimli);
    SDL_DestroyTexture(imgPionTauriel);

    SDL_DestroyTexture(case_orc);
    SDL_DestroyTexture(case_dragon);
    SDL_DestroyTexture(case_nazgul);
    SDL_DestroyTexture(case_araignee);
    SDL_DestroyTexture(case_tresor);
    SDL_DestroyTexture(case_totem);
    SDL_DestroyTexture(case_portail);
    SDL_DestroyTexture(case_baton);
    SDL_DestroyTexture(case_arc);
    SDL_DestroyTexture(case_hache);
    SDL_DestroyTexture(case_anneau);

    // LIBÉRATION AUDIO
    if (musiqueMenu != NULL) Mix_FreeMusic(musiqueMenu);
    if (musiqueJeu != NULL) Mix_FreeMusic(musiqueJeu);
    Mix_CloseAudio();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    TTF_Quit(); 
    IMG_Quit();
    SDL_Quit();
    
    return 0;  
}
