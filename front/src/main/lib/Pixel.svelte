<script lang="ts">
  import { currentTheme } from '../theme';

  export let lit: boolean = false;
  export let onClick: (buttons: number) => void;

  function onPointerMove (e: PointerEvent) {
    const target = e.target as HTMLButtonElement;
    target.releasePointerCapture(e.pointerId);
    if(e.buttons == 0){
      return;
    }
    onClick(e.buttons);
  };

$: cn = lit ? `${$currentTheme.color} size-9 rounded-full shadow-lg ${$currentTheme.shadow}` : `bg-neutral-500 hover:bg-neutral-500 size-9 rounded-full`
</script>

<button class={cn} aria-label="pixel" 
  onclick={e => onClick(e.buttons)} 
  onpointermove={onPointerMove} 
  onpointerdown={onPointerMove} 
  onpointerentercapture={onPointerMove}
  ></button>