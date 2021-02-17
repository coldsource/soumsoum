 /*
  * This file is part of evQueue
  *
  * evQueue is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * evQueue is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with evQueue. If not, see <http://www.gnu.org/licenses/>.
  *
  * Author: Thibault Kummer
  */

'use strict';

import {App} from '../base/App.js';

export class DepthMap extends React.Component {
	constructor(props) {
		super(props);
		
		this.state = {
		};
		
		App.registerComponent("map", this);
	}
	
	scalePlus() {
		App.api.command({component: "map", action: "scale_plus"});
	}
	
	scaleMinus() {
		App.api.command({component: "map", action: "scale_minus"});
	}
	
	renderRow(row) {
		let colors_neg = ["#00c1fc","#00bef8","#00bbf5","#00b8f2","#00b5ef","#00b2eb","#01afe8","#01ace5","#01a9e1","#01a6de","#01a3db","#01a0d7","#019dd4","#019ad1","#0197ce","#0193ca","#0190c7","#018dc4","#028ac0","#0287bd","#0284ba","#0281b7","#027eb3","#027bb0","#0278ad","#0275a9","#0272a6","#026fa3","#026c9f","#02699c","#036699","#036396","#036092","#035d8f","#035a8c","#035788","#035485","#035182","#034e7e","#034b7b","#034878","#034575","#044271","#043f6e","#043c6b","#043867","#043564","#043261","#042f5e","#042c5a","#042957","#042654","#042350","#04204d","#051d4a","#051a46","#051743","#051440","#05113d","#050e39"];
		let colors_pos = ["#f4c400","#f3c000","#f3bd00","#f2ba00","#f1b700","#f0b300","#efb000","#efad00","#eeaa00","#eda600","#eca300","#eba000","#eb9d00","#ea9900","#e99600","#e89300","#e79000","#e78c00","#e68900","#e58600","#e48200","#e37f00","#e37c00","#e27900","#e17500","#e07200","#df6f00","#df6c00","#de6800","#dd6500","#dc6200","#db5f00","#da5b00","#da5800","#d95500","#d85200","#d74e00","#d64b00","#d64800","#d54500","#d44100","#d33e00","#d23b00","#d23700","#d13400","#d03100","#cf2e00","#ce2a00","#ce2700","#cd2400","#cc2100","#cb1d00","#ca1a00","#ca1700","#c91400","#c81000","#c70d00","#c60a00","#c60700","#c50300"];
		
		let size = row.length;
		
		return row.map( (depth, idx) => {
			let mindepth = 100;
			let maxdepth = 1000;
			
			let col;
			let absdepth = Math.abs(depth);
			if(depth<0)
			{
				if(absdepth>mindepth)
					absdepth = mindepth;
				col = colors_neg[Math.round(absdepth/mindepth*(colors_neg.length-1))];
			}
			else
			{
				if(absdepth>maxdepth)
					absdepth = maxdepth;
				col = colors_pos[Math.round(absdepth/maxdepth*(colors_pos.length-1))];
			}
			
			if(size<40)
				return (<span key={idx} style={{backgroundColor: col}}>{depth}</span>);
			else
				return (<span key={idx} style={{backgroundColor: col}}></span>);
		});
	}
	
	renderRows() {
		return this.state.map.depthmap.map((row, idx) => {
			return (<div className="row" key={idx}>{this.renderRow(row)}</div>);
		});
	}
	
	render() {
		if(this.state.map===undefined)
			return null;
		
		return (
			<div className="DepthMap container">
				<div className="legend">Depth map</div>
				<div className="zoom">
					<span className="fa fa-minus" onClick={this.scaleMinus}></span>
					&#160;&#160;&#160;
					<span className="fa fa-plus" onClick={this.scalePlus}></span>
				</div>
				<div className="map">
					<div className="submarine">
						<img style={{transform: 'rotate('+(this.state.map.orientation-90)+'deg)'}} src="images/arrow.svg" />
					</div>
					{this.renderRows()}
				</div>
			</div>
		);
	}
}
