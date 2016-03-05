QT += widgets

HEADERS += \
    constraint.h \
    mb_cart_point.h \
    mb_vector.h \
    curv_abstract_curve.h \
    curv_ellipse.h \
    curv_line_segment.h \
    curv_nurbs.h \
    graph_curve.h \
    func_support.h \
    graph_widget.h \
    mainwindow.h

SOURCES += \
    main.cpp \
    mb_cart_point.cpp \
    mb_vector.cpp \
    curv_abstract_curve.cpp \
    curv_ellipse.cpp \
    curv_line_segment.cpp \
    curv_nurbs.cpp \
    graph_curve.cpp \
    func_support.cpp \
    graph_widget.cpp \
    mainwindow.cpp

RESOURCES += \
    GraphicEditor.qrc
