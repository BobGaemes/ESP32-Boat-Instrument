idf_component_register(
    SRCS 
        main.c
        # eth_get.c
        ui.c
        ui_image_menu_button.c
        ui_image_true_arrow.c
        ui_image_boat.c
        ui_image_apparent_arrow.c
        ui_font_montserrat.c
        screens.c
        images.c
        vars.c
        wifi_get.c
    INCLUDE_DIRS .
    PRIV_REQUIRES esp_netif esp_http_client nvs_flash bsp_extra esp_wifi
)
target_link_libraries(${COMPONENT_LIB} m)