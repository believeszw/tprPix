/*
 * ========================= Move.h ==========================
 *                          -- tpr --
 *                                        CREATE -- 2019.01.13
 *                                        MODIFY --
 * ----------------------------------------------------------
 *   Crawl / Fly 整合管理类
 * ----------------------------
 */
#ifndef _TPR_MOVE_H_
#define _TPR_MOVE_H_

//-------------------- CPP --------------------//
#include <functional>


//-------------------- Engine --------------------//
#include "Crawl.h"
#include "Fly.h"
#include "SpeedLevel.h"
#include "AnchorPos.h"
#include "MapCoord.h"

//-- need --
class GameObj;
class GameObjPos;
class Collision;



//-- 初级版本，在未来可能会发展成 数个 crawl实例 ／ 数个 fly实例
class Move{
    using F_GO  = std::function<void(GameObj*)>;
public:
    Move() = default;

    inline void init(   GameObj *_goPtr, 
                        GameObjPos *_goPosPtr,
                        Collision *_collisionPtr ){ //-- MUST --
        goPtr    = _goPtr;
        goPosPtr = _goPosPtr;

        crawl.init( goPtr, 
                    (Move*)this, 
                    goPosPtr, 
                    _collisionPtr ); 

        fly.init(   (Move*)this, 
                    goPosPtr );
    }

    inline void RenderUpdate(){
        (is_crawl_==true) ? crawl.RenderUpdate() : fly.RenderUpdate();
    }

    //---- set ----//

    inline void set_MoveType( bool _is_crawl ){
        is_crawl_ = _is_crawl;
    }

    inline bool is_crawl() const {
        return is_crawl_;
    }

    inline void set_speedLv( SpeedLevel _lv ){
        speedLv = _lv;
    }

    inline SpeedLevel get_speedLv(){
        return speedLv;
    }

    inline void set_newCrawlDir( const NineBox &_newNB ){
        assert( is_crawl_ == true );
        crawl.set_newCrawlDir( _newNB );
    }

    inline void set_newflyIns( const FlyIns &_newFlyIns ){
        assert( is_crawl_ == false );
        fly.set_newflyIns( _newFlyIns );
    }

    inline void set_maskCountLimit( int _limit ){
        assert( is_crawl_ == false );
        fly.set_maskCountLimit( _limit );
    }

    //---- get ----//

    //------ vals ------//
    F_GO  OnIdle {nullptr};  //- 当开始静止 的那一帧被调用
    F_GO  OnMove {nullptr};  //- 当开始运动 的那一帧被调用


private:
    GameObj     *goPtr    {nullptr}; //- 每个 fly实例 都属于一个 go实例, 强关联
    GameObjPos  *goPosPtr {nullptr};

    Crawl   crawl   {}; //- 未来可能被拓展为 一组 crawl实例
    Fly     fly     {}; //- 未来可能被拓展为 一组 fly实例
    bool    is_crawl_  {true};


    SpeedLevel   speedLv  { SpeedLevel::LV_3 }; //- 未来可能被拓展为 一组 speedLv数据集

};


#endif 
