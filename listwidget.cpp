#include "listwidget.h"

#include <QScrollBar>
#include <QVBoxLayout>
#include <QEvent>
#include <QStyleOption>

#include "rssfeeddata.h"
#include "rssitemdelegate.h"

ListWidget::ListWidget( QWidget * parent ) : QScrollArea( parent )
{
    auto container = new QWidget();
    auto layout = new QVBoxLayout( container );
    layout->setContentsMargins( 0, 0, 0, 0 );
    layout->setSpacing( 0 );
    layout->setSizeConstraint( QLayout::SetMinAndMaxSize );

    setWidget( container );

}

ListWidget::~ListWidget()
{
    resetListWidget();
    delete m_itemDelegate;
}


void ListWidget::setItemDelegate( RssItemDelegate * newItemDelegate )
{
    m_itemDelegate = newItemDelegate;
}

void ListWidget::setData(std::shared_ptr<RssFeedData> feedData)
{
    resetListWidget();

    Q_ASSERT( widget() != nullptr );
    Q_ASSERT( m_itemDelegate != nullptr );

    auto boxLayout = qobject_cast<QBoxLayout *>( widget()->layout() );
    Q_ASSERT( boxLayout );

    int i=0;
    for(const auto & item : qAsConst(feedData->data) )
    {
        QWidget * itemWidget = m_itemDelegate->createWidget( item, this );

        boxLayout->insertWidget( i, itemWidget, 0, Qt::AlignmentFlag::AlignTop );
        ++i;
    }
}

void ListWidget::resetListWidget()
{
    auto boxLayout = qobject_cast<QBoxLayout *>( widget()->layout() );
    Q_ASSERT( boxLayout );

    while( true )
    {
        QLayoutItem * item = boxLayout->itemAt( 0 );
        if( item == nullptr )
            break;

        auto widgetToRemove = item->widget();

        boxLayout->removeWidget( widgetToRemove );
        widgetToRemove->hide();
        widgetToRemove->deleteLater();
    }

    return;
}

bool ListWidget::event( QEvent * event )
{
    if( event->type() == QEvent::Type::LayoutRequest && widget() != nullptr )
    {
        QSize newSize = widgetResizable() ? widget()->sizeHint() : widget()->size();
        if( m_widgetSize != newSize )
        {
            m_widgetSize = newSize;
            updateGeometry();
        }
    }
    return QScrollArea::event( event );
}

QSize ListWidget::minimumSizeHint() const
{
    int f = 2 * frameWidth();
    if( frameStyle() != QFrame::NoFrame )
    {
        QStyleOption opt;
        opt.initFrom( this );
        if( style()->styleHint( QStyle::SH_ScrollView_FrameOnlyAroundContents, &opt, this ) )
        {
            f += style()->pixelMetric( QStyle::PM_ScrollView_ScrollBarSpacing, &opt, this );
        }
    }

    QSize size{ f, f };
    if( widgetResizable() == false )
    {
        int hsbExt = horizontalScrollBar()->sizeHint().height();
        int vsbExt = verticalScrollBar()->sizeHint().width();

        size.setWidth( size.width() + vsbExt );
        size.setHeight( size.height() + hsbExt );
    }

    int requiredWidth = 0;
    int requiredHeight = 0;
    auto layout = widget()->layout();
    for( int i = 0; i < layout->count(); ++i )
    {
        auto w = layout->itemAt( i )->widget();
        if( w != nullptr && w->isHidden() == false )
        {
            auto widgetMinimumSizeHint = w->minimumSizeHint();
            requiredWidth = qMax( requiredWidth, widgetMinimumSizeHint.width() );
            if( widgetResizable() )
            {
                requiredHeight += widgetMinimumSizeHint.height();
            }
        }
    }

    size.setWidth( size.width() + requiredWidth );

    if( widgetResizable() )
    {
        size.setHeight( size.height() + requiredHeight );
    }

    return size;
}

QSize ListWidget::sizeHint() const
{
    int f = 2 * frameWidth();
    if( frameStyle() != QFrame::NoFrame )
    {
        QStyleOption opt;
        opt.initFrom( this );
        if( style()->styleHint( QStyle::SH_ScrollView_FrameOnlyAroundContents, &opt, this ) )
        {
            f += style()->pixelMetric( QStyle::PM_ScrollView_ScrollBarSpacing, &opt, this );
        }
    }

    QSize sz( f, f );
    if( widget() )
    {
        m_widgetSize = widgetResizable() ? widget()->sizeHint() : widget()->size();
        sz += m_widgetSize;
    }

    if( verticalScrollBarPolicy() == Qt::ScrollBarAlwaysOn )
        sz.setWidth( sz.width() + verticalScrollBar()->sizeHint().width() );
    if( horizontalScrollBarPolicy() == Qt::ScrollBarAlwaysOn )
        sz.setHeight( sz.height() + horizontalScrollBar()->sizeHint().height() );

    return sz;
}
